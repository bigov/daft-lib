#ifndef _RIGS_HPP_
#define _RIGS_HPP_

#include "../libs/common.hpp"
#include "config.hpp"

namespace app {

	typedef char* PathName;

	// rigs.cpp
	// TODO: по-моему, это уже не надо. Все удалить.
	extern void fail(const char* fail_message);
	extern bool file_exist(const char* file_pathname);
	extern char* file_read(const char* file_pathname);

} // namespace app

#endif
