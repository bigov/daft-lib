////
// flaw.cpp
//
// Классы генерации исключений
//

#include "../hpp/flaw.hpp"

namespace app {

	Flaw::Flaw(std::string e) : err(e) { }
	std::string Flaw::what() { return err; }

	errCfg::errCfg(std::string e) : Flaw(e) { }
	errWin::errWin(std::string e) : Flaw(e) { }

} //namespace app
