/////
//
// file: window.cpp
//
// Класс создания и управления окном
//

#include "window.hpp"

namespace app
{
	////////
	// Конструктор класса
	//
	Window::Window(int w, int h, bool f): display(),	render(), actions(), ev()
	{
		iW = w;
		iH = h;
		iFS = f;
		win_center_x = iW/2;
		win_center_y = iH/2;

		// подключить обработчик событий (закрытие) окна
		SDL_EventState(SDL_WINDOWEVENT, SDL_ENABLE);

		return;
	}

	////////
	// инициализация окна
	//
	bool Window::init_window(Conf_Content * options)
	{
		const char * title = "Trickrig is running";

		id = SDL_CreateWindow(
			title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, iW, iH,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
		if(!id)
		{
			err = "Can't create window.";
			return false;
		}

		if(!getCurrentDisplayParams())
		{
			DestroyWindow(); return false;
		}

  	if(iFS == true) fullscreen_set();
		
		if(!SDL_GL_CreateContext(id))
		{	
			err = "Can't create context";
			DestroyWindow(); return false;
		}

		if(!gl::sys::LoadFunctions())
		{
			err = "Can't load OpenGl finctions";
			DestroyWindow(); return false;
		}

		if(!render.init(options))
		{
			err = render.err;
			DestroyWindow(); return false;
		}

		SDL_ShowWindow(id);

		// Отправка начальных настроек окна классу формирования контента
		render.resize(iW, iH);

		actions.btns = SDL_GetMouseState(&actions.x, &actions.y);
		actions.keys = SDL_GetKeyboardState(NULL);

		return true;
	}

	////////
	// Деструктор класса
	// 
	Window::~Window()
	{
		//write_log("window terminated");
    // Close and destroy the window
    return;
	}

	void Window::DestroyWindow()
	{
		if (nullptr != id)
		{
			SDL_DestroyWindow(id);
			id = nullptr;
		}
		return;
	}

	/////////
	// Захват окном курсора мыши
	//
	void Window::capture_mouse(void)
	{
		if(0 != SDL_CaptureMouse(SDL_TRUE))
		{
			lib::write_log("Can't capture mouse");
		}	else {
			SDL_ShowCursor(SDL_DISABLE);
			SDL_WarpMouseInWindow(id, win_center_x, win_center_y);
			mouse_captured = true;
			actions.x = win_center_x;
			actions.y = win_center_y;
		}
		return;
	}

	////////
	// Разблокировка курсора мыши
	//
	void Window::release_mouse(void)
	{
		SDL_WarpMouseInWindow(id, win_center_x, win_center_y);
		SDL_CaptureMouse(SDL_FALSE);
		SDL_ShowCursor(SDL_ENABLE);
		mouse_captured = false;
		return;
	}
	
	////////
	// проверка событий изменения рамеров окна
	//
	bool Window::check_window_events()
	{
		// отловить событие изменения размера окна
		if((SDL_PollEvent(&ev)) && (ev.type == SDL_WINDOWEVENT))
		{
			if(ev.window.event == SDL_WINDOWEVENT_CLOSE) return false;
			else if(ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				iW = ev.window.data1;
				iH = ev.window.data2;
				win_center_x = iW/2;
				win_center_y = iH/2;
				render.resize(iW, iH);
			}
		}
		
		// После опроса мыши вернуть курсор в центр окна
		if(mouse_captured) SDL_WarpMouseInWindow(id, win_center_x, win_center_y);
		else {
			if(actions.btns & SDL_BUTTON(SDL_BUTTON_LEFT)) capture_mouse();
			actions.x = win_center_x;
			actions.y = win_center_y;
		}

		// выход из цикла или освобождение курсора мыши
		if(actions.keys[SDL_SCANCODE_ESCAPE])
		{
			if(!mouse_captured) return false;
			// если захвачен - освободить
			release_mouse();
			SDL_Delay(250);
			SDL_FlushEvents(SDL_KEYDOWN, SDL_KEYUP);
			SDL_PumpEvents();
			actions.keys = SDL_GetKeyboardState(NULL);
		}

		// переключение полноэкранного режима
		if(actions.keys[SDL_SCANCODE_F11]) fullscreen();
		return true;
	}

	////////
	// Главный цикл отображения окна и обработки событий
	//
	void Window::show(Conf_Content * opt)
	{
		if (!init_window(opt)) return;
		while(check_window_events())
		{
			render.push(&actions);
			SDL_GL_SwapWindow(id);
			SDL_PumpEvents();
			actions.btns = SDL_GetMouseState(&actions.x, &actions.y);
			actions.keys = SDL_GetKeyboardState(NULL);
		}
		DestroyWindow();
		return;
	}

	////////
	// Получить режим текущего дисплея
	// (проверяются все дисплеи в системе)
	//
	bool Window::getCurrentDisplayParams()
	{
		int i;
  	for(i = 0; i < SDL_GetNumVideoDisplays(); ++i)
		{
    	if(0 ==	SDL_GetCurrentDisplayMode(i, &display)) return true;
  	}
  	err = "Can't display mode\n" + (std::string)SDL_GetError();
		return false;
	}
		
	////////
	// Fullscreen window mode switch
	// 
	void Window::fullscreen()
	{
		if(iFS) fullscreen_off();
		else fullscreen_set();

		actions.x = win_center_x = iW/2;
		actions.y = win_center_y = iH/2;
		
		// пауза четверть секунды
 		SDL_Delay(250);
		SDL_FlushEvents(SDL_KEYDOWN, SDL_KEYUP);
		SDL_PumpEvents();
		actions.keys = SDL_GetKeyboardState(NULL);

		render.resize(iW, iH);
		return;
	}

	////////
	// Setup fullscreen mode
	//
	void Window::fullscreen_set()
	{
		//запомнить размеры и положение окна до перехода в полный экран
		SDL_GetWindowPosition(id, &iX_noFS, &iY_noFS);
		SDL_GetWindowSize(id, &iW_noFS, &iH_noFS);
		
		iX = 0;
		iY = 0;
		iW = display.w;
	  iH = display.h;

		SDL_SetWindowPosition(id, iX, iY);
		SDL_SetWindowSize(id, iW, iH);
		SDL_SetWindowFullscreen(id, SDL_WINDOW_FULLSCREEN_DESKTOP);
		iFS = true;
		return;
	}

	////////
	// Set no-fullscreen window mode
	//
	void Window::fullscreen_off()
	{
		iX = iX_noFS;
		iY = iY_noFS;
		iW = iW_noFS;
	  iH = iH_noFS;
		iFS = false;

		SDL_SetWindowFullscreen(id, 0);
		SDL_SetWindowSize(id, iW, iH);
		SDL_SetWindowPosition(id, iX, iY);
		return;
	}
}
