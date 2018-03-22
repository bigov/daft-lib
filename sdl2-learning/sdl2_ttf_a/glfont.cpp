/*
  glfont:  An example of using the SDL_ttf library with OpenGL.
  Copyright (C) 2001-2013 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/* A simple program to test the text rendering feature of the TTF library */

/* quiet windows compiler warnings */
#include <cstdlib>
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>

#define WIDTH   640
#define HEIGHT  480

struct sText {
	GLuint id;
	int w;
	int h;
};

void SDL_GL_Enter2DMode(int width, int height)
{
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)width, (GLdouble)height, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		return;
}

void SDL_GL_Leave2DMode()
{
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
		glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
		return;
}

sText make_text(const char *message)
{
    sText result;
    SDL_Rect area;
    Uint8  saved_alpha;
    SDL_BlendMode saved_mode;

    if ( TTF_Init() < 0 ) fprintf(stderr, "Couldn't initialize TTF");

    TTF_Font *font = TTF_OpenFont("FreeSans.ttf", 16);
    if( NULL == font) fprintf(stderr, "Couldn't make TTF");

		TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    SDL_Color gray_color = { 0x33, 0x33, 0x33, 0 };
		SDL_Surface *sf = TTF_RenderUTF8_Blended(font, message, gray_color);
    TTF_CloseFont(font);

		result.w = sf->w;
		result.h = sf->h;

		SDL_Surface *img = SDL_CreateRGBSurface(SDL_SWSURFACE, sf->w, sf->h, 32,
		#if SDL_BYTEORDER == SDL_LIL_ENDIAN
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
		#else
			0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
    #endif
		);

    if (NULL == img) return result;

    /* Save the alpha blending attributes */
    SDL_GetSurfaceAlphaMod(sf, &saved_alpha);
    SDL_SetSurfaceAlphaMod(sf, 0xFF);
    SDL_GetSurfaceBlendMode(sf, &saved_mode);
    SDL_SetSurfaceBlendMode(sf, SDL_BLENDMODE_NONE);

    /* Copy the surface into the GL texture image */
    area.x = 0;
    area.y = 0;
    area.w = sf->w;
    area.h = sf->h;
    SDL_BlitSurface(sf, &area, img, &area);

    /* Restore the alpha blending attributes */
    SDL_SetSurfaceAlphaMod(sf, saved_alpha);
    SDL_SetSurfaceBlendMode(sf, saved_mode);

    /* Create an OpenGL texture for the image */
		GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
		result.id = texture;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sf->w, sf->h, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
    SDL_FreeSurface(img);
    SDL_FreeSurface(sf);

		if( glGetError() != GL_NO_ERROR ) fprintf(stderr, "Error create text");

    return result;
}

/* Show the text on the screen */
void show_text(sText text)
{
	// Coordinates
	int x = 8;
	int y = 0;

	SDL_GL_Enter2DMode(WIDTH, HEIGHT);
  glBindTexture(GL_TEXTURE_2D, text.id);
  glBegin(GL_TRIANGLE_STRIP);
  glTexCoord2f(0.0, 0.0); glVertex2i(x, y);
  glTexCoord2f(1.0, 0.0); glVertex2i(x + text.w, y);
  glTexCoord2f(0.0, 1.0); glVertex2i(x, y + text.h);
  glTexCoord2f(1.0, 1.0); glVertex2i(x + text.w, y + text.h);
  glEnd();
  SDL_GL_Leave2DMode();
	return;
}

int main(int argc, char *argv[])
{
    SDL_Window *window = SDL_CreateWindow("glfont",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

		sText label = make_text("Тестовое сообщение для тестирования");

    /* Wait for a keystroke, and blit text on mouse press */
    int done = 0;
    SDL_Event event;
    while ( ! done ) {
        while ( SDL_PollEvent(&event) ) {
            switch (event.type) {
                case SDL_KEYDOWN: case SDL_QUIT:
									done = 1;
									break;
                default:
									break;
            }
        }

        /* Clear the screen */
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				show_text(label);

        /* Swap the buffers so everything is visible */
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);

    TTF_Quit();
    SDL_Quit();
    exit(0);
}
