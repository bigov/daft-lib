////
//
//	file: server.hpp
//
//
#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "../libs/common.hpp"
#include "config.hpp"

namespace app
{
	class Server
	{
		private:
			Conf_Server * opt;
		public:
			Server(Conf_Server * options);
			void start(void);
			void stop(void);
	};

} //namespace app

#endif
