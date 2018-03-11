#ifndef tcputil_h
#define tcputil_h

#include <string>
#include <SDL2/SDL_net.h>

namespace lib {

/* receive a buffer from a TCP socket with error checking */
/* this function handles the memory, so it can't use any [] arrays */
/* returns 0 on any errors, or a valid char* on success */
int getMsg(TCPsocket sock, std::string &);

/* send a string buffer over a TCP socket with error checking */
/* returns 0 on any errors, length sent on success */
int putMsg(TCPsocket sock, const std::string &);

}
//namespace lib

#endif
