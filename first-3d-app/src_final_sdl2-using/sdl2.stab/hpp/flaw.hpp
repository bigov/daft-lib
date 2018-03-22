////
//
//	file: flaw.hpp
//
//
#ifndef __FLAW_HPP__
#define __FLAW_HPP__

#include "../libs/common.hpp"

namespace app {

	////
	// Базовый класс генерации исключений
	//
	class Flaw
	{
		protected:
			std::string err;

		public:
			Flaw(std::string error_message);
			virtual ~Flaw(void) {};
			virtual std::string what();
	};

	class errCfg : public Flaw
	{	
		public:
			errCfg(std::string message);
	};

		class errWin : public Flaw
	{	
		public:
			errWin(std::string message);
	};

} //namespace app

#endif

