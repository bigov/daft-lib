//
// Интерфейс передачи классам-подписчикам сообщений из класса окна
//
// Типы сообщений:
//
// 	1. Изменение параметров (изменение геометрии, сворачивание, закрытие)
// 	2. Взаимодействие с пользователем (нажатие кнопок клавиатуры/мыши)
//
#ifndef _SWOP_HPP_
#define _SWOP_HPP_

#include "config.hpp"
#include "../libs/rigs/glslprog.hpp"

namespace app {

/*
// стиль движения/состояние персонажа
// лежать, сидеть, стоять, красться, идти, бежать, лететь, карабкаться
enum Rods { LIE, SIT, STAND, CREEP, WALK, RUN, FLY, CLIMB };
*/

// направление и вид движения (6 векторов) диапазон: [-127 : 127]
struct Moving {
	signed char x = 0;
	signed char y = 0;
	signed char z = 0;
	signed char a = 0;	// азимут
	signed char t = 0;  // тангаж
	signed char r = 0;  // крен
};

// список событий окна
enum WindowEvents { NO_EVENTS, CLOSE, MOVE, RESIZE, FOCUS_ON, FOCUS_OFF,
	FULLSCREEN_ON, FULLSCREEN_OFF };

// список событий взаимодействия с пользователем
enum KeysEvents { KEY_UP, KEY_DOWN, MOUSE_UP, MOUSE_DOWN, MOUSE_MOVE };

// Структура для передачи клиенту изменений параметров окна
struct ParamsWindow {
	WindowEvents ev; // event type
	int w;    			 // window width
	int h;    			 // window height
};

// действия пользователя в окне
struct ActionsUser {
	KeysEvents ev;// нажато/отпущено
	int  key;			// клавиша/кнопка
	int  mx;    	// координата X курсора мыши
	int  my;   		// координата Y курсора мыши
	int  dx;    	// сдвиг курсора мыши по оси Х
	int  dy;  		// сдвиг курсора мыши по оси Y
};

////////
//  Отрисовка контента 3D средствами GLSL шейдерной программы
//
class Content3D
{
	private:
		float win_aspect;
		Moving mov;
		Conf_Content * cfg;
		GLSLProgram * prog;
		void set_vertices(void);
		void set_draw_order(void);
		void set_texcoords(void);
		void make_view(void);
		void render_content(void);
		void free_resources(void);
		void resize_viewport(int, int);

	public:
		std::string err;
		Content3D();
		~Content3D(void);
		bool init(Conf_Content *);
		void push_params(ParamsWindow);
		void push_moving(Moving);
};

////////
// Интерфейс передачи состояния и событий окна
//
class Interface_WE
{
	private:
		ParamsWindow params;
		Moving mov;
		Content3D content;

	public:
		std::string err = "";

		Interface_WE(void);
		bool init(Conf_Content *);
		void push_e(ParamsWindow);
		void push_a(const ActionsUser &);
};

} //namespace app
#endif //_SWOP_HPP_
