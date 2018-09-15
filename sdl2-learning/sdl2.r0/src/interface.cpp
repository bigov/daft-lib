////////
//
// Определения классов интефейса передачи данных их окна класса
// в класс рендера
//

#include "interface.hpp"

namespace app {

	////////
	// Конструктор класса.
	//
	// Тут назначаются клавиши управления по-умолчанию. В дальнейшем можно
	// сделать простую процедуру для их переназначения
	//
	Interface_WE::Interface_WE(): mov(), content(), err("") {}

	////
	// Инициализировать 3D контент
	//
	bool Interface_WE::init(Conf_Content * options)
	{
		if(content.init(options)) return true;
		else
		{
			err = content.err;
			return false;
		}
	}

	////
	// Отправка сообщения о событии окна
	void Interface_WE::resize(int w, int h)
	{
		center_x = w/2;
		center_y = h/2;
		content.resize_viewport(w, h);
		return;
	}

	////////
	// обработчик сдвига мыши
	// возвращает вектор движения взгляда
	//
	glm::vec3 Interface_WE::looking(const ActionsUser * a)
	{
		mov.a += (float)(a->x - center_x) * sence_mouse;
		mov.t -= (float)(a->y - center_y) * sence_mouse;

		mov.a += (float)a->keys[lookRight] * sence_keys;
		mov.a -= (float)a->keys[lookLeft]  * sence_keys;
		mov.t += (float)a->keys[lookUp]    * sence_keys;
		mov.t -= (float)a->keys[lookDown]  * sence_keys;

		if(mov.a > two_pi) mov.a -= two_pi;
		if(mov.a < 0) mov.a += two_pi;

		if(mov.t > look_up) mov.t = look_up;
		if(mov.t < look_down) mov.t = look_down;

		return {(float)(cos(mov.a)*cos(mov.t)),
				(float)sin(mov.t),
				(float)(sin(mov.a)*cos(mov.t))
		};
	}

	////////
	// обработчик нажатий клавиш управления движением
	// возвращает вектор смещения в зависимости от вектора взляда
	//
	// Внимание! Функция зависит от значения азимута камеры (mov.a), поэтому
	// должна вызываться только ПОСЛЕ вызова Interface_WE::looking(), которая
	// устанавливает значение "mov.a" на основании перемещения курсора мыши или
	// клавиш управления направление взгляда
	//
	glm::vec3 Interface_WE::moving(const ActionsUser * a)
	{
		float x = (float)(a->keys[keyRight]   - a->keys[keyLeft]);
		float y = (float)(a->keys[keyUp]      - a->keys[keyDown]);
		float z = (float)(a->keys[keyForward] - a->keys[keyBack]);

		return {
			z*cos(mov.a) + x*sin(mov.a - pi), y, z*sin(mov.a) + x*cos(mov.a)
		};
	}

	////
	// Отправка сообщения о действии пользователя в рендер 3D сцены
	void Interface_WE::push(const ActionsUser * a)
	{
		glm::vec3 look = looking(a);
		glm::vec3 move = moving(a);

		content.rendering(look, move);
		return;
	}

} //namespace app
