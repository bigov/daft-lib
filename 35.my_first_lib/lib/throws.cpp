////
// flaw.cpp
//
// Классы генерации исключений
//

#include "throws.hpp"

namespace lib {

	Flaw::Flaw(std::string e) : err(e) { }
	std::string Flaw::what() { return err; }

	errCfg::errCfg(std::string e) : Flaw(e) { }
	errWin::errWin(std::string e) : Flaw(e) { }

	errShader::errShader(std::string m, lib::defShader d)	: Flaw(m), def(d) { }
	std::string errShader::what() { return def.name +": " + err; }

} //namespace lib
