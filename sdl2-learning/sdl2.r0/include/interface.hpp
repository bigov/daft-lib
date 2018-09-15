//
// Интерфейс передачи классам-подписчикам сообщений из класса окна
//
// Типы сообщений:
//
// 	1. Изменение параметров (изменение геометрии, сворачивание, закрытие)
// 	2. Взаимодействие с пользователем (нажатие кнопок клавиатуры/мыши)
//
#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include "config.hpp"
#include "content3d.hpp"

namespace app {

////////
// Интерфейс передачи состояния и событий окна
//
class Interface_WE
{
	private:
		// клавиши управления (сделать возможность менять)
		Uint8 keyForward  = SDL_SCANCODE_W;
		Uint8 keyBack     = SDL_SCANCODE_S;
		Uint8 keyLeft     = SDL_SCANCODE_A;
		Uint8 keyRight    = SDL_SCANCODE_D;
		Uint8 keyDown     = SDL_SCANCODE_LSHIFT;
		Uint8 keyUp       = SDL_SCANCODE_SPACE;
		float sence_mouse = 0.001f;
		
		// управление взглядом при помощи клавиш
		Uint8 lookUp      = SDL_SCANCODE_UP;
		Uint8 lookDown    = SDL_SCANCODE_DOWN;
		Uint8 lookLeft    = SDL_SCANCODE_LEFT;
		Uint8 lookRight   = SDL_SCANCODE_RIGHT;
		float sence_keys  = 0.03f;

		Moving mov;
		int speed = 1;	// скорость движения при нажатии клавиш
		int center_x = 0;
		int center_y = 0;

		Content3D content;
		glm::vec3 looking(const ActionsUser *);
		glm::vec3 moving(const ActionsUser *);

	public:
		std::string err;
		Interface_WE(void);
		bool init(Conf_Content *);
		void resize(int pixels_width, int pixels_height);
		void push(const ActionsUser *);
};

} //namespace app
#endif //__INTERFACE_HPP__
