////
//
// Класс для работы с окном графического приложения
//
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "lib.hpp"
#include "config.hpp"
#include "interface.hpp"

namespace app
{
	class Window
	{
		private:
			int iX = 0; // положение окна
			int iY = 0; //
			int iW = 0;
			int iH = 0;
			int win_center_x = 0;
			int win_center_y = 0;

			int iX_noFS = 0;	// Сохранение значений для восстановления размера
			int iY_noFS = 0;  // и положения окна после возврата из полноэкранного
			int iW_noFS = 0;  // режима
			int iH_noFS = 0;

			bool iFS = false;
			SDL_DisplayMode display;
			SDL_Window * id = nullptr;
			bool mouse_captured = false;
			Interface_WE render;
			ActionsUser actions;
	 		SDL_Event ev;

			bool getCurrentDisplayParams(void);
			bool init_window(Conf_Content *);
			void fullscreen(void);
			void fullscreen_set(void);
			void fullscreen_off(void);
			void capture_mouse(void);
			void release_mouse(void);
			void DestroyWindow(void);
			bool check_window_events();
			Window(const Window &);
			Window operator=(const Window &);

		public:
			std::string err = "";
			Window(int width, int height, bool fullscreen);
			~Window();
			void show(Conf_Content *);
	};
} //namespace app

#endif //__WINDOW_H__
