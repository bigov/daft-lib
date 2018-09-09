////
// Базовые библиотеки для всех компонентов приложения
//
#ifndef __LIB_H__
#define __LIB_H__

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <list>
#include <algorithm>

#include <SDL2/SDL.h> 
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_image.h>

// add libs on the path ../libs
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gl_com_3.hpp"

namespace lib {

//// file: io.cpp"|------------------------------------
extern void show_error     (const std::string &);
extern void show_message   (const std::string &);
extern void write_log      (const std::string &);
extern void set_log_fname  (const std::string &);
extern void out_debug_file (const std::string &);
extern void msg_out_console(const std::string &);
extern bool filepath_ok    (const std::string &);
extern bool sdl_file_exist(const char* file_pathname);
extern char* sdl_file_read(const char* file_pathname); 
// ----------------------------------------------------|

struct defShader
{
	GLenum id;
	std::string name;
};

} //namespace lib
#endif // __LIB_H__
