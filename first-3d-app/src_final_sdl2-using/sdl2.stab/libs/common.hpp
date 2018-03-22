////
// Базовые библиотеки для всех компонентов приложения
//
#ifndef _COMMON_HPP_
#define _COMMON_HPP_

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
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef __MS_WIN__
#include "gl_load_gen/mswin/gl_com_4_5.hpp"
#else
#include "gl_load_gen/linux/gl_com_4_5.hpp"
#endif

// Глобальная переменная, перенаправляющая PopUp сообщения в журнал
extern int RELEASE;

//// file: "rigs/messages.cpp"|-----------------
extern void show_error     (const std::string &);
extern void show_message   (const std::string &);
extern void write_log      (const std::string &);
extern void set_log_fname  (const std::string &);
extern void out_debug_file (const std::string &);
extern void msg_out_console(const std::string &);

extern bool filepath_ok    (const std::string &);
// ---------------------------------------------|

#endif //COMMON_HPP
