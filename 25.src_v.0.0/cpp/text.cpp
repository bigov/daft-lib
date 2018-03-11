/*
 * sText label = make_text("Тестовое сообщение для тестирования");
 * show_text(label);
 */

#include "rigs.hpp"
#include <SDL2/SDL_ttf.h>

namespace app {

struct sText {
	GLuint id;
	int w;
	int h;
};

void set_2d(int width, int height)
{
    gl::PushAttrib(gl::ENABLE_BIT);
    gl::Disable(gl::DEPTH_TEST);
    gl::Disable(gl::CULL_FACE);
    gl::Enable(gl::TEXTURE_2D);
    gl::Enable(gl::BLEND);
    gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
    //gl::Viewport(0, 0, width, height);
    gl::MatrixMode(gl::PROJECTION);
    gl::PushMatrix();
    gl::LoadIdentity();
    gl::Ortho(0.0, (GLdouble)width, (GLdouble)height, 0.0, 0.0, 1.0);
    gl::MatrixMode(gl::MODELVIEW);
    gl::PushMatrix();
    gl::LoadIdentity();
    //gl::TexEnvf(gl::TEXTURE_ENV, gl::TEXTURE_ENV_MODE, gl::MODULATE);
		return;
}

void set_3d()
{
    gl::MatrixMode(gl::MODELVIEW);
    gl::PopMatrix();
		gl::MatrixMode(gl::PROJECTION);
    gl::PopMatrix();
    gl::PopAttrib();
		return;
}

sText make_text(const char *message)
{
    sText result;
    SDL_Rect area;
    Uint8 saved_alpha;
    SDL_BlendMode saved_mode;

    if ( TTF_Init() < 0 ) SDL_Log("Couldn't initialize TTF");

    TTF_Font *font = TTF_OpenFont("FreeSans.ttf", 16);
    if(!font) fail("Couldn't create TTF_Font object");

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
    gl::GenTextures(1, &texture);
    gl::BindTexture(gl::TEXTURE_2D, texture);
		result.id = texture;

		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);
    gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, sf->w, sf->h, 0,
				gl::RGBA, gl::UNSIGNED_BYTE, img->pixels);
    SDL_FreeSurface(img);
    SDL_FreeSurface(sf);

		if(gl::GetError()) SDL_Log("Error create text");

    return result;
}

/* Show the text on the screen */
void show_text(const char *message, int screen_w, int screen_h)
{
	// Coordinates
	int x = 8;
	int y = 0;

	sText text = make_text(message);

	set_2d(screen_w, screen_h);
	//gl::BindTexture(gl::TEXTURE_2D, text.id);
	gl::Begin(gl::TRIANGLE_STRIP);
	gl::TexCoord2f(0.0, 0.0); gl::Vertex2i(x, y);
  gl::TexCoord2f(1.0, 0.0); gl::Vertex2i(x + text.w, y);
  gl::TexCoord2f(0.0, 1.0); gl::Vertex2i(x, y + text.h);
  gl::TexCoord2f(1.0, 1.0); gl::Vertex2i(x + text.w, y + text.h);
  gl::End();
  set_3d();
	return;
}

} // namespace app
