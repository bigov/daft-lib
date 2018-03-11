////
//
// Описание классов исключений для всех компонентов приложения
//
#ifndef __THROWS_H__
#define __THROWS_H__

#include "lib.hpp"

namespace lib {

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
		virtual std::string what(void);
};

////
// ошибки конфига
//
class errCfg : public Flaw
{	
	public:
		errCfg(std::string message);
};

////
// ошибки окон
//
class errWin : public Flaw
{	
	public:
		errWin(std::string message);
};	

////
// Ошибки компиляции шейдеров
//
class errShader : public Flaw
{
	protected:
		defShader def;
	public:
		errShader(std::string err_message, defShader define);
		virtual ~errShader(void) {};
		virtual std::string what(void);
};

} //namespace lib
#endif // __THROWS_H__
