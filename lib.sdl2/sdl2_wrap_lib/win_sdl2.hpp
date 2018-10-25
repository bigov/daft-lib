#ifndef _WIN_SDL2_HPP_
#define _WIN_SDL2_HPP_

#include "config.hpp"
#include "gl_com_3.hpp"
#include <SDL2/SDL.h>

namespace tr
{

	class WindowSDL2
	{
		private:
			WindowSDL2(const tr::WindowSDL2&);
			operator=(const tr::WindowSDL2&);

			SDL_DisplayMode display;
			SDL_Window * win_id = nullptr;
			SDL_Event ev;

			int w;
			int h;

			void destroy_window(void);

		public:
			WindowSDL2(tr::Config &);
			~WindowSDL2(void);
			void init_content(void);
			void show(void (*renderer_function)(void));
	};

} //namespace tr
#endif //_WIN_SDL2_HPP_
