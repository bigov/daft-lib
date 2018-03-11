/**
 * Application graphic interface
 */

#include "gui.hpp"

namespace app
{
	// Constractor
	GUI::GUI() {
		const char *title = "Trickrig is running";

		guiX = new int(0);
		guiY = new int(0);
		cfg = new Config();
		guiW = new int(*cfg->win0_w);
		guiH = new int(*cfg->win0_h);

		win0_ratio = new float(0.0);
		*win0_ratio = (float)*guiW/(float)*guiH;

		/*
		if(0 != ( SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, cfg->major)
						+ SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, cfg->minor))
			) fail("Can't set OpenGL content version");
		*/
		if(0 != (	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, cfg->major) +
							SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, cfg->minor) +
							SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) +
							SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
								SDL_GL_CONTEXT_PROFILE_COMPATIBILITY) )
			) fail("Can't set OpenGL content version");

		if(SDL_GetDesktopDisplayMode(0, &displayMode)) fail("No display mode.");

		win0 = SDL_CreateWindow(
			title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, *guiW, *guiH,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

		if(!win0) fail("Can't create window.");
		// Create OpenGL context
		if(!SDL_GL_CreateContext(win0)) fail("Can't create context");
		// Init OpenGL functions and extensions
		if(!gl::sys::LoadFunctions()) fail("Can't load OpenGl finctions");
		return;
	}

	// Destructor
	GUI::~GUI()
	{
		free_resources();
		flash_params();
		delete cfg;
		delete guiW;
		delete guiH;
		delete guiX;
		delete guiY;
		delete win0_ratio;
		return;
	}

	void GUI::flash_params()
	{
		// сохранить размеры окна до перехода в полноэкранный режим
		if(1 == *cfg->win0_f)
		{
			*cfg->win0_w = *guiW;
			*cfg->win0_h = *guiH;
		}
		return;
	}

	// Обработка изменений размера окна как при перемещении границ окна,
	// так и при переключении в полноэкранный режим и обратно.
	void GUI::onResize(int width, int height) {
		*cfg->win0_w = width;
		*cfg->win0_h = height;
		*win0_ratio = (float)width/(float)height;
		gl::Viewport(0, 0, width, height);
		return;
	}

	void GUI::fullscreen_enable()
	{
		//запомнить размеры и положение окна до перехода в полный экран
		SDL_GetWindowPosition(win0, guiX, guiY);
		SDL_GetWindowSize(win0, guiW, guiH);

		SDL_SetWindowPosition(win0, 0, 0);
		SDL_SetWindowSize(win0, displayMode.w, displayMode.h);
		SDL_SetWindowFullscreen(win0, SDL_WINDOW_FULLSCREEN_DESKTOP);
		*cfg->win0_f = 1;
		return;
	}

	void GUI::fullscreen_disable()
	{
		SDL_SetWindowFullscreen(win0, 0);
		SDL_SetWindowSize(win0, *guiW, *guiH);
		SDL_SetWindowPosition(win0, *guiX, *guiY);
		*cfg->win0_f = 0;
		return;
	}

	// Full screen main application window
	void GUI::switch_fullscreen()
	{
		if (1 == *cfg->win0_f){
			fullscreen_disable();
		} else {
			fullscreen_enable();
		}
		return;
	}

	void GUI::show()
	{
		content_create(cfg);
		SDL_LogVerbose(APP, "Content created");
		SDL_Event ev;
		bool loop = true;
		bool mouse_captured = false;
		Rods gait;

		if(*cfg->win0_f) fullscreen_enable();
		SDL_ShowWindow(win0);

		while (loop) {
			render_content(*win0_ratio, gait);
			SDL_GL_SwapWindow(win0);
			SDL_PollEvent(&ev);
			switch(ev.type)
			{
				case SDL_QUIT: return;

				case SDL_WINDOWEVENT:
					if( ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						onResize(ev.window.data1, ev.window.data2);
					} else {
						ev.window.event = 0;
					}
					break;

				case SDL_KEYDOWN:
					if( !gait.up && (ev.key.keysym.sym == SDLK_SPACE) ){
						gait.up = true;
					} else if( !gait.down && (ev.key.keysym.sym == SDLK_LSHIFT) ){
						gait.down = true;
					} else {
						ev.key.keysym.sym = 0;
					}
					break;

				case SDL_KEYUP:
					if(ev.key.keysym.sym == SDLK_ESCAPE) {
						ev.key.keysym.sym = 0;
						if(!mouse_captured) {	loop = false;	}
						else {
							int pos_x = (int)(*guiW)/2;
							int pos_y = (int)(*guiH)/2;
							SDL_WarpMouseInWindow(win0, pos_x, pos_y);
							SDL_CaptureMouse(SDL_FALSE);
							SDL_ShowCursor(SDL_ENABLE);
							SDL_LogVerbose(APP, "Mouse released");
							mouse_captured = false;	}
					} else if (ev.key.keysym.sym == SDLK_F11){
						switch_fullscreen();
					} else if( gait.up && (ev.key.keysym.sym == SDLK_SPACE) ){
						gait.up = false;
					} else if( gait.down && (ev.key.keysym.sym == SDLK_LSHIFT) ){
						gait.down = false;
					} else {
						ev.key.keysym.sym = 0;
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					if(!mouse_captured)
					{
						if(0 != SDL_CaptureMouse(SDL_TRUE))
						{
							SDL_Log("Can't capture mouse");
						}	else {
							SDL_ShowCursor(SDL_DISABLE);
							SDL_LogVerbose(APP, "Mouse captured");
							mouse_captured = true;
						}
					}
					break;

				default: break;
			}
		}
		return;
	}

} //namespace app

