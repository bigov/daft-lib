/**
 * wikibook: http://en.wikibooks.org/wiki/OpenGL_Programming
 * This file is in the public domain.
 * Contributors: Sylvain Beucler
 */
#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gl_com_4_5.hpp"

#ifndef _CREATE_SHADER_H
#define _CREATE_SHADER_H

extern char* file_read(const char* filename, int* size);
extern void print_log(GLuint object);
extern GLuint create_shader(const char* filename, GLenum type);
extern GLuint create_program(const char* vertexfile, const char *fragmentfile);
extern GLuint create_gs_program(const char* vertexfile,
		const char *geometryfile, const char *fragmentfile, GLint input,
		GLint output, GLint vertices);
extern GLint get_attrib(GLuint program, const char *name);
extern GLint get_uniform(GLuint program, const char *name);
extern void print_opengl_info();

#endif
