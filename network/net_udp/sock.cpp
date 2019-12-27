//////////////////////////////////////////////////////////////////////////////
//
// file: sock.cpp
//
// Класс неблокируемого UDP сокета
//
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////

#include "sock.hpp"

namespace lib {

////////
// Посимвольный прием из консоли строки _s c ограничением по длине
//
int cinString(std::string & _s, int max)
{
	int _c;
	_s.clear();
	int i = 0;
	while((_c = std::getchar()) != cR && i++ < max) _s += (char)_c;
	if( i > max)
	{ // если превышено ограничение, то сбросить все и вернуть ошибку (-1)
		_s.clear();
		while((_c = std::getchar()) != cR) continue;
		return -1;
	}
	return i;
}

////////
// Формирование структуры адреса для работы с сокетом
//
// Входные параметры:
//
//	- ip: строка существующего IP адреса существующего интерфейса. Если
// 		передана пустая строка, то сокет слушает на всех адресах (0.0.0.0)
//
//	- p: номер порта для открытия сокета. Если передан "0", то порт выбирается
//		системой произвольно.
//
sockaddr_in makeSockaddrIn(const std::string & ip, short unsigned p)
{
	sockaddr_in _a;
	_a.sin_family = AF_INET;
	if(ip.empty()) _a.sin_addr.s_addr = INADDR_ANY;
	else _a.sin_addr.s_addr = inet_addr(ip.c_str());
	_a.sin_port = htons(p);
	return _a;
}

////////
// Конструктор класса
//
SocketNonBlockUDP::SocketNonBlockUDP():soc(),ip(),port(0),err(){}

////////
// Открыть сокет с указанным номером порта
//
bool SocketNonBlockUDP::open(short unsigned p)
{
	err.clear();

	soc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(lib::socket_fail(soc))
		err += "\nFailure init socket.";

	// адрес для открытия сокета
	sockaddr_in addrClient = lib::makeSockaddrIn("", p);

	// окрыть сокет
	if(bind(soc, (sockaddr*)&addrClient, sizeof(sockaddr_in) ) < 0)
		err += "\nFailed to bind socket.";

	// получить адрес и порт сокета
	if(!lib::SocketGetName(soc, &addrClient))
	{
    err += "\nFailed to get socket params";
	} else {
		ip = inet_ntoa(addrClient.sin_addr);
		port = ntohs(addrClient.sin_port);
	}

	// перевести сокет в неблокирующий режим
	if(!lib::SocketNonBlocked(soc))
		err += "\nFailed to set Socket_Non_Blocked mode";
	
	if(err.empty()) return true;
	else return false;
}

////////
// Можно открыть сокет с портом по выбору системы
//
bool SocketNonBlockUDP::open(void){ return SocketNonBlockUDP::open(0); }

////////
// деструктор
//
SocketNonBlockUDP::~SocketNonBlockUDP(void)
{
	lib::SocketClose(soc);	 // закрыть соединение
}


}//namespace lib
