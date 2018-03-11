//////////////////////////////////////////////////////////////////////////////
//
// file: server_udp.cpp
//
// Модуль для создания простого UDP сервиса на назначенном порту
//
// СПРАВКА: преобразование "структура <-> адрес"
// ----------------------------------
// inet_aton("10.0.0.1", &antelope.sin_addr); // store IP in antelope
// some_addr = inet_ntoa(antelope.sin_addr); // return the IP
//
//////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <thread>
#include <queue>
#include <mutex>

#include "sock.hpp"

#define DEFAULT_SERVER_PORT 4422

std::chrono::milliseconds ms10(10);
std::chrono::milliseconds ms50(50);

// очередь для приема и обработки команд (через консоль)
std::queue<std::string> messages;
std::mutex mutex_cmd; // разграничение доступа к буферу ввода
lib::SocketNonBlockUDP s; //сокет
bool run = true;

////////
// прием (в отдельном потоке) команд через консоль сервера
void cin_input()
{
	std::string s;
	int l;
	int max = 128;
	while(run)
	{
		// Прием команд из консоли сервера. Прием производится в режиме ожидания
		// ввода от оператора - цикл в этом месте остановлен, пока не придет "l"
		l = lib::cinString(s, max);
	
		if(l > 0)
		{ // если прията команда, то она заносится в потокобезопасную очередь
			// для последующего извлечения и обработки в другом потоке
			while(!mutex_cmd.try_lock()) std::this_thread::sleep_for(ms10);
			messages.push(s);
			mutex_cmd.unlock();
		}

		if(s == "/Q") run = false;	// команда выхода из цикла
		// разгрузочная пауза
		std::this_thread::sleep_for(ms50);
	}

	std::cout << "Input was terminated." << std::endl;
	return;
}

////////
// отправка данных "buf" на сокет с адресом "a"
void net_responce(char * buf, const sockaddr_in & a)
{
	if(!lib::SocketSendChars(s.soc, buf, (sockaddr*)&a))
		std::cout << "failure to send UDP packet." << std::endl;
	return;
}

////////
// прием данных по сети
void net_receive()
{
	int max = 128;
	char * buf = new char[max];

	while(run)
	{
		sockaddr_in a;
		socklen_t a_len = sizeof(&a);

		int received = lib::SocketReceiveChars(s.soc, buf, max, &a, &a_len);
		if (received < 1 )
		{
			std::this_thread::sleep_for(ms10);
		}
		else
		{
			std::cout <<"["<<inet_ntoa(a.sin_addr)<<":"
				<<ntohs(a.sin_port) <<"] " <<buf <<cR;
			net_responce(buf, a);
		}
	}
	delete [] buf;

	return;
}

////////
// выбор и открытие порта
//
bool open_port(int argc, char * argv[])
{
	short unsigned int srv_port;
	/* get the port from the commandline, if exist and correct */
	if(argc == 2) srv_port = (short unsigned int)strtol(argv[1], nullptr, 0);
	if(srv_port == 0) srv_port = DEFAULT_SERVER_PORT;

	if(!s.open(srv_port))
	{ // если не удалось открыть сокет, напечатать номер порта и завершить
		std::cout << "Can't open "<< srv_port <<" port. Terminate." <<cR;
		return false;
	} else
	{ // вывести номер открытого порта сокета для подключений
		std::cout << "Listen on " << s.ip << ":" << s.port <<cR <<cR;
	}

	return true;
}

int main(int argc, char * argv[])
{
	// создание сокета
	lib::SocketsLibInit();
	
	if(!open_port(argc, argv)) return 1;
	
	// поток приема команд с консоли
	std::thread input(cin_input);
 	input.detach();

	net_receive();

	lib::SocketsLibClose();				// освободить ресурсы
	std::cout <<"Service stop, quit." <<cR;
	return 0;
}
