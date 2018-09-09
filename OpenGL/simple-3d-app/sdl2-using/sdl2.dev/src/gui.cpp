/**
 * Application graphic interface
 */

#include "gui.hpp"

namespace app
{
	////////
	// Constructor of the class
	//
	GUI::GUI(Conf_GUI * config) : cfg(config)
	{
		if(0 != (	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, cfg->major) +
							SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, cfg->minor) +
							SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) +
							SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
							SDL_GL_CONTEXT_PROFILE_COMPATIBILITY) ))
			throw std::runtime_error("Can't set OpenGL content attributes");

		// Отключить все неиспользуемые  обработчики событий. После этого для
		// каждой подсистемы необходимо активировать свои обработчики отдельно
		// по мере необходимости
		// 
		SDL_EventState(SDL_QUIT, SDL_IGNORE);
		SDL_EventState(SDL_APP_TERMINATING, SDL_IGNORE);
		SDL_EventState(SDL_APP_LOWMEMORY, SDL_IGNORE);
		SDL_EventState(SDL_APP_WILLENTERBACKGROUND, SDL_IGNORE);
		SDL_EventState(SDL_APP_DIDENTERBACKGROUND, SDL_IGNORE);
		SDL_EventState(SDL_APP_WILLENTERFOREGROUND, SDL_IGNORE);
		SDL_EventState(SDL_APP_DIDENTERFOREGROUND, SDL_IGNORE);
		SDL_EventState(SDL_WINDOWEVENT, SDL_IGNORE);
		SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
		SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
		SDL_EventState(SDL_KEYUP, SDL_IGNORE);
		SDL_EventState(SDL_TEXTEDITING, SDL_IGNORE);
		SDL_EventState(SDL_TEXTINPUT, SDL_IGNORE);
		SDL_EventState(SDL_KEYMAPCHANGED, SDL_IGNORE);
		SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
		SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
		SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
		SDL_EventState(SDL_MOUSEWHEEL, SDL_IGNORE);
		SDL_EventState(SDL_JOYAXISMOTION, SDL_IGNORE);
		SDL_EventState(SDL_JOYBALLMOTION, SDL_IGNORE);
		SDL_EventState(SDL_JOYHATMOTION, SDL_IGNORE);
		SDL_EventState(SDL_JOYBUTTONDOWN, SDL_IGNORE);
		SDL_EventState(SDL_JOYBUTTONUP, SDL_IGNORE);
		SDL_EventState(SDL_JOYDEVICEADDED, SDL_IGNORE);
		SDL_EventState(SDL_JOYDEVICEREMOVED, SDL_IGNORE);
		SDL_EventState(SDL_CONTROLLERAXISMOTION, SDL_IGNORE);
		SDL_EventState(SDL_CONTROLLERBUTTONDOWN, SDL_IGNORE);
		SDL_EventState(SDL_CONTROLLERBUTTONUP, SDL_IGNORE);
		SDL_EventState(SDL_CONTROLLERDEVICEADDED, SDL_IGNORE);
		SDL_EventState(SDL_CONTROLLERDEVICEREMOVED, SDL_IGNORE);
		SDL_EventState(SDL_CONTROLLERDEVICEREMAPPED, SDL_IGNORE);
		SDL_EventState(SDL_FINGERDOWN, SDL_IGNORE);
		SDL_EventState(SDL_FINGERUP, SDL_IGNORE);
		SDL_EventState(SDL_FINGERMOTION, SDL_IGNORE);
		SDL_EventState(SDL_DOLLARGESTURE, SDL_IGNORE);
		SDL_EventState(SDL_DOLLARRECORD, SDL_IGNORE);
		SDL_EventState(SDL_MULTIGESTURE, SDL_IGNORE);
		SDL_EventState(SDL_CLIPBOARDUPDATE, SDL_IGNORE);
		SDL_EventState(SDL_DROPFILE, SDL_IGNORE);
		SDL_EventState(SDL_AUDIODEVICEADDED, SDL_IGNORE);
		SDL_EventState(SDL_AUDIODEVICEREMOVED, SDL_IGNORE);

		return;
	}

	////////
	// Построение графического интерфейса. (пока только одно 3D окно) 
	//
	void GUI::show(Conf_Content * options)
	{
		Window W0(cfg->W, cfg->H, cfg->F);
		W0.show(options);
		//std::thread twin(&Window::show, &W0, options);
		//twin.join();
		if("" != W0.err) lib::show_error(W0.err);
		return;
	}

	////////
	// Destructor of the class
	//
	GUI::~GUI()
	{
		// сохранить размеры окна при работе в полноэкранном режим
		if(1 == cfg->F)
		{
			/*
			cfg->W = *guiW;
			cfg->H = *guiH;
			*/
		}
		return;
	}

} //namespace app
