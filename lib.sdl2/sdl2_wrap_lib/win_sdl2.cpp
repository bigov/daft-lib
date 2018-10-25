#include <iostream>
#include "win_sdl2.hpp"

namespace tr
{

	////////
	// Инициализация библиотеки SDL2
	//
	void init_lib_sdl(void)
	{
		if(0 != SDL_Init(SDL_INIT_EVERYTHING))
			throw std::runtime_error("Can't init SDL-lib.");
		
		//if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
		//	throw std::runtime_error("Can't init SDL2_image lib");
		return;
	}

	////////
	// Конструктор
	//
	WindowSDL2::WindowSDL2(tr::Config & cfg):
		display(), ev(), w(cfg.gui.w), h(cfg.gui.h)

	{
		init_lib_sdl();
		init_content();
		return;
	}

	////////
	// Деструктор
	//
	WindowSDL2::~WindowSDL2()
	{
		destroy_window();
		return;
	}

	////////
	// Создание окна и инициализация OpenGL контента
	//
	void WindowSDL2::init_content(void)
	{
		const char * title = "TR";

		if(!(win_id = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, w, h,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)))
		{
			throw std::runtime_error("Can't create SDL_WINDOW_OPENGL");
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		
		if(!SDL_GL_CreateContext(win_id))
		{	
			destroy_window();
			throw std::runtime_error("Can't create context");
		}
		// For no limit FPS (no VSync) set:
		// 	SDL_GL_SetSwapInterval(0);
		// 
		// Here is set VSync:
		SDL_GL_SetSwapInterval(1);

		return;
	}

	////////
	// Цикл отображения окна
	//
	void WindowSDL2::show(void content_rendering())
	{
		while(ev.window.event != SDL_WINDOWEVENT_CLOSE)
		{
			content_rendering();
			SDL_GL_SwapWindow(win_id);
			SDL_PollEvent(&ev);
		}
		
		destroy_window();
		return;
	}

	////////
	// Удаление объекта "Window" штатными средствами SDL2
	//
	void WindowSDL2::destroy_window()
	{
		if (nullptr != win_id)
		{
			SDL_DestroyWindow(win_id);
			win_id = nullptr;
		}
		return;
	}


} //namespace tr
