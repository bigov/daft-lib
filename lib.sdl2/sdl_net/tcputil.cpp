#include <iostream>
#include <string>
#include <climits>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

namespace lib {
using std::string;

////////
// Отправка строки с сообщением в сокет. 
//
// Отправка производится в два приема - вначале передается длина строки,
// предназначенной для отправки, а затем сама строка.
//
// Функция возвращает длину переданной строки или 0 (в случае ошибки)
int putMsg(TCPsocket sock, const string & message)
{
	int size_send_len, result;

	size_t message_length = message.length() + 1;
	if(message_length > INT_MAX)
	{
		printf("Message lenght more than INT_MAX");
		return 0;
	}

	// передать размер посылаемого сообщения, перестроив в соответствии со
	// стандартом передачи по TCP/IP очередность байт в передаваемом числе
	Uint32 send_len = SDL_SwapBE32((Uint32)message_length);
	size_send_len = (int)sizeof(send_len);
	result = SDLNet_TCP_Send(sock, &send_len, size_send_len);
	
	if(result < size_send_len)
	{
		if(SDLNet_GetError() && strlen(SDLNet_GetError()))
			printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return 0;
	}
	
	// передать само сообщение
	char * buf = new char[message_length];
	buf[message.copy(buf, string::npos)] = '\0';
	size_send_len = (int)message_length;
	// TODO проверить работоспособность через message.c_str() вместо buf
	result = SDLNet_TCP_Send(sock, buf, size_send_len);
	delete buf;

	if(result < size_send_len)
	{
		if(SDLNet_GetError() && strlen(SDLNet_GetError()))
			printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return 0;
	}
	return result;
}

/* receive a buffer from a TCP socket with error checking */
/* this function handles the memory, so it can't use any [] arrays */
/* returns 0 on any errors, or a valid char* on success */

int getMsg(TCPsocket sock, string & message)
{
	int result;

	Uint32 msg_len; // размер принимаемого сообщения
	int size_of_len = (int)sizeof(msg_len);
	result = SDLNet_TCP_Recv(sock, &msg_len, size_of_len); // получить размер
	
	if(result < size_of_len)
	{
		if(SDLNet_GetError() && strlen(SDLNet_GetError()))
			printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
		return 0;
	}
	
	// восстановить порядок байт в принятом по TCP/IP числе
	msg_len = SDL_SwapBE32(msg_len);
	if(msg_len == 0) return 0;
	if(msg_len > INT_MAX)
	{
		printf("Recived lenght of message more than INT_MAX");
		return 0;
	}

	// выделить память под буфер
	char * buf = new char[msg_len];
	int len = (int)msg_len;
	/* get the string buffer over the socket */
	result = SDLNet_TCP_Recv(sock, buf, len);
	
	if(result < len)
	{
		if(SDLNet_GetError() && strlen(SDLNet_GetError())) /* sometimes blank! */
			printf("SDLNet_TCP_Recv: %s\n", SDLNet_GetError());
		return 0;
	} else {
		message = string(buf, strlen(buf));
	}
	
	delete [] buf;
	return result;
}

} //namespace lib

