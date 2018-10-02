#ifndef _RIGS_H
#define _RIGS_H

#include <cstdlib>
#include <iostream>

/* #include "ext/gl_core_2_1.h" */
#include "ext/gl_core_3_0.hpp"
#include <SDL2/SDL.h>

// Content of src file: "shader_tr.c"
extern char* file_read(const char* filename);
extern void print_log(GLuint object);
extern GLuint create_shader(const char* filename, GLenum type);

#endif
