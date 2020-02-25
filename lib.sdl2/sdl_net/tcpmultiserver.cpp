#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "tcputil.hpp"

class Client
{
	private:
		Client operator=(const Client &);
		Client (const Client &);

	public:
		Client(void) : sock(0), name() {};
		Client(TCPsocket s, std::string n) : sock(s), name(n) {};
		TCPsocket sock;
		std::string name;
};

// регистронезависимое сравнение символов
inline bool CharsCmpN(char a, char b) { return(toupper(a) == toupper(b)); }
// регистронезависимое сравнение строк
bool StringsCmpN(const std::string & s1, const std::string & s2)
{
  return((s1.size() == s2.size()) &&
     equal(s1.begin(), s1.end(), s2.begin(), CharsCmpN));
}

std::list<Client *> clients;
TCPsocket server;

void send_all(std::string message);
Client * get_client_byName(const std::string & name);

/* terminate the nick at "bad" characters... */
std::string fix_nick(const std::string & nick)
{
	char * s = new char[nick.length() + 1];
	s[nick.copy(s, std::string::npos)] = '\0';

	size_t i;
	if((i = strspn(s, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQR"
		"STUVWXYZ|_=+.,:;/\\?!@#$%^&*()~`")) != strlen(s)) s[i]='\0';
	
	std::string result(s, strlen(s));
	delete [] s;
	return result;
}

/* test for nice name uniqueness among already connected users */
int unique_nick(std::string s)
{
	if(nullptr == get_client_byName(s)) return 1;
	else return 0;
}

////////
// Обрезать конец строки после символа "sep"
//
std::string strsep(std::string src, const char * sep)
{
	size_t pos = src.find(sep);
	if(pos > src.length()) return src;
	return src.substr(0, pos);
}

////////
// Поиск клиента по номеру сокета
//
Client * get_client_bySocket(TCPsocket s)
{
	for(auto member: clients) if( member->sock == s) return member;
	return nullptr;
}

////////
//	Поиск клиента по имени
//
Client * get_client_byName(const std::string & n)
{
	for(auto member: clients) if( member->name == n) return member;
	return nullptr;
}

/* create a socket set that has the server socket and all the client sockets */
SDLNet_SocketSet create_sockset()
{
	static SDLNet_SocketSet set = NULL;
	if(set) SDLNet_FreeSocketSet(set);
	set = SDLNet_AllocSocketSet((int)clients.size() + 1);
	if(!set) {
		std::cout << "SDLNet_AllocSocketSet: " << SDLNet_GetError() << std::endl;
		exit(1); /*most of the time this is a major error, but do what you want. */
	}
	SDLNet_TCP_AddSocket(set, server);
	for(auto member: clients) SDLNet_TCP_AddSocket(set, member->sock);
	return set;
}

/* send a buffer to all clients */
void send_all(std::string msg)
{
	if(msg.empty() || clients.empty())	return;

	for(auto member: clients)
	{
		if(1 < lib::putMsg(member->sock, msg)) clients.remove(member);
	}
	return;
}

void do_command(const std::string & p, Client * client)
{
	if(p.empty() || nullptr == client)	return;

	std::string command = strsep(p," ");
	/* /NICK : change the clients name */
	if(command.find("NICK") == 0)
	{
		std::string old_name=client->name;
		
		std::string new_name = fix_nick(p);
		if(new_name.length() < 2)
		{
			lib::putMsg(client->sock,"--- Invalid Nickname!");
			return;
		}
		if(!unique_nick(new_name))
		{
			lib::putMsg(client->sock,"--- Duplicate Nickname!");
			return;
		}
		client->name = new_name;
		send_all("--- " + old_name + " --> " + new_name);
		return;
	}
	/* MSG : client to client message */
	if(StringsCmpN(command, "MSG"))
	{
		std::string name;
		//Client to_client;
		if(!p.empty())
		{
			name = strsep(p," ");
			Client * to_client = get_client_byName(name);
			if(nullptr == to_client)
			{
				lib::putMsg(client->sock,
					"--- /MSG nickname " + (std::string)name + " not found!");
				return;
			}
			lib::putMsg(client->sock, ">" + name + "< " + p);
			lib::putMsg(to_client->sock, ">" + client->name + "< " +p);
			return;
		}
		lib::putMsg(client->sock,"--- /MSG nickname message...");
		return;
	}
	/* /ME : emote! to everyone */
	if(StringsCmpN(command, "ME"))
	{
		if(!p.empty()) send_all(client->name + " " + p);
		else lib::putMsg(client->sock,"--- /ME message...");
		return;
	}
	/* /QUIT : quit the server with a message */
	if(StringsCmpN(command, "QUIT"))
	{
		if(p.empty() || StringsCmpN(p, "-h"))
		{
			if(!p.empty())
				send_all("--- " + client->name + " quits : " + p);
			else
				send_all("--- " + client->name + " quits");
			clients.remove(get_client_bySocket(client->sock));
		}
		else
			lib::putMsg(client->sock,"--- /QUIT [message...]");
		return;
	}
	/* /WHO : list the users online back to the client */
	if(StringsCmpN(command, "WHO"))
	{
		IPaddress * ipaddr;
		Uint32 ip;
		const char * host = NULL;
		
		lib::putMsg(client->sock,"--- Begin /WHO ");

		for(auto member: clients)
		{
			ipaddr=SDLNet_TCP_GetPeerAddress(member->sock);
			if(ipaddr)
			{
				ip = SDL_SwapBE32(ipaddr->host);
				host = SDLNet_ResolveIP(ipaddr);
				lib::putMsg(client->sock,
					"--- " + member->name +	host + " [" + std::to_string(ip>>24) + "."
					+ std::to_string((ip>>16)&0xff) + "." + std::to_string((ip>>8)&0xff)
					+ "." + std::to_string(ip&0xff) + "] port " +
					std::to_string((Uint32)ipaddr->port));
			}
		}

		lib::putMsg(client->sock, "--- End /WHO");
		return;
	}
	/* /HELP : tell the client all the supported commands */
	if(StringsCmpN(command,"HELP"))
	{
		lib::putMsg(client->sock,"--- Begin /HELP");
		lib::putMsg(client->sock,"--- /HELP : this text");
		lib::putMsg(client->sock,"--- /ME message... : emote!");
		lib::putMsg(client->sock,"--- /MSG nickname message... : personal messaging");
		lib::putMsg(client->sock,"--- /NICK nickname : change nickaname");
		lib::putMsg(client->sock,"--- /QUIT [message...] : disconnect this client");
		lib::putMsg(client->sock,"--- /WHO : list who is logged on");
		lib::putMsg(client->sock,"--- End /HELP");
		return;
	}

	/* invalid command...respond appropriately */
	lib::putMsg(client->sock,
		"--- What does the '" + (std::string)command + "' command do?");
}

////////
// Инициализация сервера
//
void srv_init()
{
	IPaddress ip;
	Uint16 port = 4422;
	
	/* initialize SDL */
	if(SDL_Init(0) == -1)
	{
		std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
		exit(1);
	}

	/* initialize SDL_net */
	if(SDLNet_Init() ==  -1)
	{
		std::cout << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
		SDL_Quit();
		exit(2);
	}

	/* Resolve the argument into an IPaddress type */
	if(SDLNet_ResolveHost(&ip, NULL, port) == -1)
	{
		std::cout << "SDLNet_ResolveHost: "<<SDLNet_GetError()<<std::endl;
		SDLNet_Quit();
		SDL_Quit();
		exit(3);
	}

	std::cout << "Listening port: " << port << std::endl << std::endl;

	/* open the server socket */
	server=SDLNet_TCP_Open(&ip);
	if(!server)
	{
		std::cout << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
		SDLNet_Quit();
		SDL_Quit();
		exit(4);
	}
	return;
}

////////
// Main server work cycle
//
void srv_loop()
{
	TCPsocket sock;
	SDLNet_SocketSet set;
	std::string message;

	while(1)
	{
		set = create_sockset();
		if(-1 == SDLNet_CheckSockets(set, (Uint32)-1))
		{
			std::cout << "SDLNet_CheckSockets: " << SDLNet_GetError() << std::endl;
			break;
		}
		
		if(SDLNet_SocketReady(server))
		{
			/*printf("Connection...\n"); */
			sock = SDLNet_TCP_Accept(server);
			if(sock)
			{
				std::string name;

				/*printf("Accepted...\n"); */
				if(lib::getMsg(sock, name))
				{
					Client client(sock, name);
					clients.push_back(& client);
					do_command("WHO", &client);
				}
				else
					SDLNet_TCP_Close(sock);
			}
		}
		for(auto _cli: clients)
		{
			if(SDLNet_SocketReady(_cli->sock))
			{
				if(lib::getMsg(_cli->sock, message))
				{
					std::cout << "<" << _cli->name << ">" << message << std::endl;
					/* interpret commands */
					if(message[0]=='/' && message.size() > 1)
					{
						do_command(message.substr(1), _cli);
					}
					else /* it's a regular message */
					{
						/* forward message to ALL clients... */
					send_all("<" + _cli->name + "> " + message);
					}
				}
				else
					clients.remove(_cli);
			}
		}
	}
	return;
}

////////
// MAIN
//
int main(int argc, char **argv)
{
	if(argc) argc = 0;
	*argv = nullptr;

	srv_init();
	srv_loop();

	SDLNet_Quit();
	SDL_Quit();

	return 0;
}
