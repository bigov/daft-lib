/*
  gl::font:  An example of using the SDL_ttf library with Opengl::.
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
#include "glfont.hpp"

void SDL_GL_Enter2DMode(int width, int height)
{
    gl::PushAttrib(gl::ENABLE_BIT);
    gl::Disable(gl::DEPTH_TEST);
    gl::Disable(gl::CULL_FACE);
    gl::Enable(gl::TEXTURE_2D);
    gl::Enable(gl::BLEND);
    gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
    gl::Viewport(0, 0, width, height);
    gl::MatrixMode(gl::PROJECTION);
    gl::PushMatrix();
    gl::LoadIdentity();
    gl::Ortho(0.0, (GLdouble)width, (GLdouble)height, 0.0, 0.0, 1.0);
    gl::MatrixMode(gl::MODELVIEW);
    gl::PushMatrix();
    gl::LoadIdentity();
    gl::TexEnvf(gl::TEXTURE_ENV, gl::TEXTURE_ENV_MODE, gl::MODULATE);
		return;
}

void SDL_GL_Leave2DMode()
{
    gl::MatrixMode(gl::MODELVIEW);
    gl::PopMatrix();
		gl::MatrixMode(gl::PROJECTION);
    gl::PopMatrix();
    gl::PopAttrib();
		return;
}

SDL_Surface* text_surf(const char *text)
{
    if ( TTF_Init() < 0 ) fprintf(stderr, "Couldn't initialize TTF");
    TTF_Font *font = TTF_OpenFont("FreeSans.ttf", 18);
    if( NULL == font) fprintf(stderr, "Couldn't make TTF");
		TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    SDL_Color _color = { 0x0, 0x0, 0x0, 1 };
		SDL_Surface *sf = TTF_RenderUTF8_Blended(font, text, _color);
    TTF_CloseFont(font);

		return sf;
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

    /* Copy the surface into the gl:: texture image */
    area.x = 0;
    area.y = 0;
    area.w = sf->w;
    area.h = sf->h;
    SDL_BlitSurface(sf, &area, img, &area);

    /* Restore the alpha blending attributes */
    SDL_SetSurfaceAlphaMod(sf, saved_alpha);
    SDL_SetSurfaceBlendMode(sf, saved_mode);

    /* Create an Opengl:: texture for the image */
		GLuint texture;
    gl::GenTextures(1, &texture);
    gl::BindTexture(gl::TEXTURE_2D, texture);
		result.id = texture;

		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);

    gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, sf->w, sf->h, 0,
				gl::RGBA, gl::UNSIGNED_BYTE, img->pixels);
    
		SDL_FreeSurface(img);
    SDL_FreeSurface(sf);

		if(!gl::GetError()) fprintf(stderr, "Error create text");

    return result;
}

/* Show the text on the screen */
void show_text(sText text)
{
	// Coordinates
	int x = 8;
	int y = 0;

  gl::BindTexture(gl::TEXTURE_2D, text.id);
  gl::Begin(gl::TRIANGLE_STRIP);
  gl::TexCoord2f(0.0, 0.0); gl::Vertex2i(x, y);
  gl::TexCoord2f(1.0, 0.0); gl::Vertex2i(x + text.w, y);
  gl::TexCoord2f(0.0, 1.0); gl::Vertex2i(x, y + text.h);
  gl::TexCoord2f(1.0, 1.0); gl::Vertex2i(x + text.w, y + text.h);
  gl::End();

	return;
}
