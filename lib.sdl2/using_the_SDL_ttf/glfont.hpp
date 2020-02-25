
#include <cstdlib>
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gl_com_4_5.hpp"

struct sText {
	GLuint id;
	int w;
	int h;
};

extern void SDL_GL_Enter2DMode(int width, int height);
extern void SDL_GL_Leave2DMode();
extern sText make_text(const char *message);
extern void show_text(sText text);
extern SDL_Surface* text_surf(const char *text);

