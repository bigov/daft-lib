// platform detection
#define OS_WIN 1
#define OS_MAC 2
#define OS_NIX 3

// в Makefile указать: [ -D_WIN32 | -D_APPLE ]
#if defined(_WIN32)
	#define PLATFORM OS_WIN
#elif defined(_APPLE)
	#define PLATFORM OS_MAC
#else
	#define PLATFORM OS_NIX
#endif

#if PLATFORM == OS_WIN
	// in here is: SOCKET == unsigned int
	#include <winsock2.h>
#elif PLATFORM == OS_MAC || PLATFORM == OS_NIX
	typedef int SOCKET;
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>
#endif

#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>

std::chrono::milliseconds ms50(50);
std::chrono::seconds sec10(10);
std::mutex mutex_cmd;
bool run = true;
std::queue<std::string> messages;

////////
// 	MS-Windows требует перед началом работы с сокетами вызвать функцию
// 	инициализации функционала. Для *nix это не требуется.
//
//	TODO: надо разобраться, следует ли данную функцию вызывать перед
//	созданием каждого нового сокета, или вызвать только один раз в начале
//	работы с сокетами.
//
inline bool SocketsInit()
{
	#if PLATFORM == OS_WIN
		WSADATA WsaData;
		return WSAStartup( MAKEWORD(2,2), &WsaData ) == NO_ERROR;
	#else
  	return true;
  #endif
}

////////
// В MS-Windows после использования сокетов надо вызовать функцию очистки
//
inline void SocketsFree()
{
	#if PLATFORM == OS_WIN
		WSACleanup();
	#endif
	return;
}

////////
// В MS-Windows SOCKET == unsgnet int
// В *nix       SOCKET == int
//
inline bool socket_fail(SOCKET s)
{
	#if PLATFORM == OS_WIN
  	return s == INVALID_SOCKET;
	#else
		return s < 1;
	#endif
}

////////
//	Установка сокета в неблокирующий режим работы
//
inline bool SocketNonBlocked(SOCKET s)
{
	#if PLATFORM == OS_WIN
		DWORD nonBlocking = 1;
    return SOCKET_ERROR != ioctlsocket(s, (long)FIONBIO, &nonBlocking);
	#else //if PLATFORM == OS_MAC || PLATFORM == OS_NIX
		int nonBlocking = 1;
		return -1 != fcntl(s, F_SETFL, O_NONBLOCK, nonBlocking);
	#endif
}

////////
// Закрытие сокета
//
inline void SocketClose(SOCKET s)
{
	#if PLATFORM == OS_MAC || PLATFORM == OS_NIX
		close(s);
	#elif PLATFORM == OS_WIN
		closesocket(s);
	#endif
	return;
}

//////////////////////////////////////////////////////////////////////////////

////////
// прием данных из стандартного потока
//
void cmd_cin() 
{
	while(run)
	{
		std::string cmd;
		std::cin >> cmd;
		while(!mutex_cmd.try_lock()) std::this_thread::sleep_for(ms50);
		messages.push(cmd);
		mutex_cmd.unlock();
		if(cmd == "q") run = false;
	}
	std::cout << "Input was terminated." << std::endl;
	return;
}
////////
// Вывод данных
void cmd_cout()
{
	bool loop = true;
	while (loop)
	{
		std::this_thread::sleep_for(sec10);
		std::string cmd;
		while(!mutex_cmd.try_lock()) std::this_thread::sleep_for(ms50);
		if(!messages.empty())
		{
			cmd = messages.front();
			messages.pop();
		} else {
			cmd = "Command queue is empty.";
			loop = run; // разрешить выход только если очередь пуста
		}
		mutex_cmd.unlock();
		std::cout << "state: " << cmd << std::endl;
	}
	std::cout << "Output was terminated." << std::endl;
	return;
}

int main() 
{
	// создание сокета
	SocketsInit();
	SOCKET handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(socket_fail(handle))
	{
		std::cout << "filure init socket\n";
		SocketsFree();
		return 1;
	}

	// открытие сокета
	unsigned short port = 0; // выбор произвольного порта
	sockaddr_in address_from;
	address_from.sin_family = AF_INET;
	address_from.sin_addr.s_addr = INADDR_ANY;
	address_from.sin_port = htons(port); // для 32-х разрядных чисел - "htonl"
	// окрыть сокет
	if(bind(handle, (sockaddr*)&address_from, sizeof(sockaddr_in) ) < 0)
	{
		std::cout << "failed to bind socket\n";
		return false;
	}

	// перевод сокета в неблокирующий режим
	if(!SocketNonBlocked(handle))
	{
		std::cout << "failed to set Socket_Non_Blocked mode\n";
		return false;
	}
	
	//// Отправка пакетов
	//==========================================================================
	
	// получатель: 127.0.0.1:4422
	unsigned int a = 127;
	unsigned int b = 0;
	unsigned int c = 0;
	unsigned int d = 1;
	unsigned short p = 4422;

	unsigned int destination_address = (a << 24) | (b << 16) | (c << 8) | d;
	unsigned short destination_port = p;

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(destination_address);
	address.sin_port = htons(destination_port);
	
	// отправить данные
	const char * packet_data = "hi from me";
	int packet_size = sizeof(packet_data);

  int sent_bytes = sendto(handle, packet_data, packet_size, 0,
		(sockaddr*)&address, sizeof(sockaddr_in) );

	if(sent_bytes != packet_size)
	{
		std::cout << "Failed to send UDP packet. Return value = " << sent_bytes
			<< std::endl;
		return false;
	}
	
	//// Прием пакетов
	//==========================================================================
	
	while ( true )
 	{
		unsigned char packet_data[256];
		int maximum_packet_size = sizeof( packet_data );

		sockaddr_in from;
		int fromLength = sizeof(from);

		int received_bytes = recvfrom(handle, (char*)packet_data,
			maximum_packet_size, 0, (sockaddr*)&from, &fromLength);

		if ( received_bytes < 1 ) break;

		//unsigned int from_address = ntohl( from.sin_addr.s_addr );
		//unsigned int from_port = ntohs( from.sin_port );

	}

	SocketClose(handle);	// закрыть соединение
	SocketsFree();				// освободить ресурсы

	////------------------------------------------------------------------------
	std::thread input(cmd_cin);
 	input.detach();
	cmd_cout();


	std::cout << "Application was closed." << std::endl;
	return 0;
}
