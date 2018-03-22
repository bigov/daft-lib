//////////////////////////////////////////////////////////////////////////////
// 
// file: socketnonblockudp.hpp
//
// Заголовок класса создания неблокируемого UDP сокета
//
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////
#ifndef __SOCKETNONBLOCKUDP_HPP__
#define __SOCKETNONBLOCKUDP_HPP__

#include <string>
#include "sockets.hpp"

#define cR '\n'

namespace lib {

sockaddr_in makeSockaddrIn(const std::string & ip, short unsigned port);
int cinString(std::string & buffer, int max_size);

class SocketNonBlockUDP
{
	private:
		SocketNonBlockUDP(const SocketNonBlockUDP &);
		SocketNonBlockUDP operator=(const SocketNonBlockUDP &);

	public:
		SOCKET soc;
		std::string ip;
		short unsigned port;
		std::string err;

		SocketNonBlockUDP(void);
		~SocketNonBlockUDP(void);
		bool open(void);
		bool open(short unsigned socket_port);
};

} // namespace lib
#endif
