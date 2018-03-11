////
//
// Класс для работы с окном графического приложения
//
#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "../libs/common.hpp"
#include "config.hpp"
#include "swop.hpp"
#include "rigs.hpp"
#include "3d.hpp"


namespace app
{
	class Window
	{
		private:
			int iX; // Текущие размеры для передчи параметров окна
			int iY; // рендеру контента
			int iW;
			int iH;

			int iX_noFS;	// Сохранение значений для восстановления размера
			int iY_noFS;  // и положения окна после возврата из полноэкранного
			int iW_noFS;  // режима
			int iH_noFS;

			int iFS;
			SDL_DisplayMode display;
			SDL_Window * id = nullptr;
			bool mouse_captured;
			Interface_WE swop;

			bool getCurrentDisplayParams(void);
			bool init_window(Conf_Content *);
			void fullscreen(void);
			void fullscreen_set(void);
			void fullscreen_off(void);
			void capture_mouse(void);
			void release_mouse(void);
			bool next_loop(void);
			void DestroyWindow(void);

		public:
			std::string err;
			Window(int width, int height, int fullscreen);
			~Window();
			void show(Conf_Content *);
	};
} //namespace app

#endif //_WINDOW_HPP_
