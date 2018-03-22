/**
 * Application graphic interface
 */

#include "../hpp/gui.hpp"

namespace app
{
	////////
	// Constructor of the class
	//
	GUI::GUI(Conf_GUI * config) throw(Flaw) : cfg(config)
	{
		if(0 != (	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, cfg->major) +
							SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, cfg->minor) +
							SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) +
							SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
							SDL_GL_CONTEXT_PROFILE_COMPATIBILITY) ))
			throw Flaw("Can't set OpenGL content attributes");

		return;
	}

	////////
	// main loop
	//
	void GUI::show(Conf_Content * options) throw(Flaw)
	{
		Window W0 = Window(cfg->W, cfg->H, cfg->F);
		std::thread twin(&Window::show, &W0, options);
		twin.join();
		if("" != W0.err) throw Flaw(W0.err);
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
