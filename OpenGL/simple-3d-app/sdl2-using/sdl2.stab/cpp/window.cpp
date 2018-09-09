////
// file: window.cpp
//
// Класс создания и управления окном
//

#include "../hpp/window.hpp"

namespace app
{
	////////
	// Конструктор класса
	//
	Window::Window(int w, int h, int f): iW(w), iH(h), iFS(f),
		mouse_captured(false), err("")  { }

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

  	if(1 == iFS) fullscreen_set();
		
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

		if(!swop.init(options))
		{
			err = swop.err;
			DestroyWindow(); return false;
		}

		SDL_ShowWindow(id);
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
			SDL_Log("Can't capture mouse");
		}	else {
			SDL_ShowCursor(SDL_DISABLE);
			mouse_captured = true;
		}
		return;
	}

	////////
	// Разблокировка курсора мыши
	//
	void Window::release_mouse(void)
	{
		int pos_x = (int)(iW)/2;
		int pos_y = (int)(iH)/2;
		SDL_WarpMouseInWindow(id, pos_x, pos_y);
		SDL_CaptureMouse(SDL_FALSE);
		SDL_ShowCursor(SDL_ENABLE);
		mouse_captured = false;
		return;
	}
	
	////////
	// Продолжение главного цикла после нажатия клавиши выхода
	bool Window::next_loop(void)
	{
		if(!mouse_captured) return false;
		else release_mouse();
		return true;
	}

	////////
	// Цикл отображения окна и обработки событий
	// 
	void Window::show(Conf_Content * opt)
	{
		// Создание и отображения окна с контентом
		if (!init_window(opt)) return;

		// Отправка начальных настроек окна классу формирования контента
		swop.push_e({RESIZE, iW, iH});

		SDL_Event ev;
		bool loop = true;
		ActionsUser action;

		while (loop) {

			if(SDL_PollEvent(&ev))
			{
				switch(ev.type)
				{
					case SDL_QUIT:
						loop = false;
						break;

					case SDL_WINDOWEVENT:
						if( ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
						{
							iW = ev.window.data1;
							iH = ev.window.data2;
							swop.push_e({RESIZE, iW, iH});
						}
						break;

					case SDL_KEYDOWN:
						if(ev.key.keysym.sym == SDLK_ESCAPE) loop = next_loop();
						action.ev = KEY_DOWN;
						action.key = ev.key.keysym.sym;
						swop.push_a(action);
						break;

					case SDL_KEYUP:
						if(ev.key.keysym.sym == SDLK_F11)
						{ 
							fullscreen();
							swop.push_e({RESIZE, iW, iH});
						}
						else 
						{
							action.ev = KEY_UP;
							action.key = ev.key.keysym.sym;
							swop.push_a(action);
						}
						break;

					case SDL_MOUSEBUTTONDOWN:
						if(!mouse_captured) capture_mouse();
				/*
				case SDL_AUDIODEVICEADDED:
				case SDL_AUDIODEVICEREMOVED:
				case SDL_CONTROLLERAXISMOTION:
				case SDL_CONTROLLERBUTTONDOWN:
				case SDL_CONTROLLERBUTTONUP:
				case SDL_CONTROLLERDEVICEADDED:
				case SDL_CONTROLLERDEVICEREMOVED:
				case SDL_CONTROLLERDEVICEREMAPPED:
				case SDL_DOLLARGESTURE:
				case SDL_DOLLARRECORD:
				case SDL_DROPFILE:
				case SDL_FINGERMOTION:
				case SDL_FINGERDOWN:
				case SDL_FINGERUP:
				case SDL_JOYAXISMOTION:
				case SDL_JOYBALLMOTION:
				case SDL_JOYHATMOTION:
				case SDL_JOYBUTTONDOWN:
				case SDL_JOYBUTTONUP:
				case SDL_JOYDEVICEADDED:
				case SDL_JOYDEVICEREMOVED:
				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEWHEEL:
				case SDL_MULTIGESTURE:
				case SDL_SYSWMEVENT:
				case SDL_TEXTEDITING:
				case SDL_TEXTINPUT:
				case SDL_USEREVENT:
				*/
					default:
						swop.push_e({NO_EVENTS, iW, iH});
						break;
				} // end switch

			}
			else // no events in the query
			{
				swop.push_e({NO_EVENTS, iW, iH});
			}// end if

		SDL_GL_SwapWindow(id);
		}// loop end

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
		if (iFS) fullscreen_off();
		else fullscreen_set();
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
		iFS = 1;
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
		iFS = 0;

		SDL_SetWindowFullscreen(id, iFS);
		SDL_SetWindowSize(id, iW, iH);
		SDL_SetWindowPosition(id, iX, iY);
		return;
	}
}
