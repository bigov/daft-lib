//////////////////////////////////////////////////////////////////////////////
//
// file: sockets.hpp
//
// Мультиплатформенная библиотека для работы с UDP сокетами.
//
// Сделано по мотивам публикации:
// http://gafferongames.com/networking-for-game-programmers/udp-vs-tcp/
// переведенной на Хабрахабре: https://habrahabr.ru/post/209524/
//
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __SOCKETS_H__
#define __SOCKETS_H__

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
	typedef int socklen_t;
#elif PLATFORM == OS_MAC || PLATFORM == OS_NIX
	typedef int SOCKET;
	#define SOCKET_ERROR -1
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <fcntl.h>
	#include <unistd.h>
#endif

#include <iostream>
#include <cstring>

namespace lib {

////////
// Прием через сокет символьной строки
// (адрес отправителя вносятся в "sockaddr * from")
//
// Возвращает число(int) принятых символов
//
inline int SocketReceiveChars(SOCKET s, char * buf,
	int buf_len, sockaddr_in * from, socklen_t * from_len)
{
#if PLATFORM == OS_WIN
	return recvfrom(s, buf, buf_len, 0,
			(sockaddr*)from, from_len);
#else
	return (int)recvfrom(s, buf, (size_t)buf_len, 0,
			(sockaddr*)from, from_len);
#endif
}

////////
// Отправка через сокет по адресу получателя символьной строки
//
inline bool SocketSendChars(SOCKET s, char * data, sockaddr * dst)
{
#if PLATFORM == OS_WIN
		int packet_size = (int)strlen(data) + 1;
		return( packet_size == sendto(s, data, packet_size, 0,
			dst, sizeof(sockaddr_in)) );
#else
		size_t packet_size = strlen(data) + 1;
		return( packet_size == (size_t)sendto(s, data, packet_size, 0,
			dst, sizeof(sockaddr_in)) );
#endif
}

////////
// Получение данных сокета (адрес, порт...)
//
//	char * ip_addr = inet_ntoa(name.sin_addr);
//	int port = ntohs(name.sin_port);
//
inline bool SocketGetName(SOCKET s, sockaddr_in * name)
{
	#if PLATFORM == OS_WIN
		int n_l = sizeof(*name);
	#else
		unsigned int n_l = sizeof(*name);
	#endif
	return (SOCKET_ERROR != getsockname(s, (sockaddr*)name, &n_l));
}
	//int n_l = sizeof (addrClient);
	//getsockname(handle, (sockaddr*)&addrClient, &n_l);


////////
// 	MS-Windows требует перед началом работы с сокетами вызвать функцию
// 	инициализации функционала. Для *nix это не требуется.
//
//	TODO: надо разобраться, следует ли данную функцию вызывать перед
//	созданием каждого нового сокета, или вызвать только один раз в начале
//	работы с сокетами.
//
inline bool SocketsLibInit(void)
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
inline void SocketsLibClose(void)
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
} //namespace lib

#endif // __SOCKETS_H__
