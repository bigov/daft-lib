//============================================================================
//
// file: content.hpp
//
//
//
//============================================================================
#ifndef __CONTENT3D_HPP__
#define __CONTENT3D_HPP__

#include <algorithm>

#include "config.hpp"
#include "bits.hpp"
#include "glslprog.hpp"

namespace app {

const	float two_pi = glm::two_pi<glm::float_t>();
const	float half_pi = glm::half_pi<glm::float_t>();
const	float _half_pi = 0 - half_pi;
const	float look_up = half_pi - 0.01f;
const	float look_down = 0 - half_pi + 0.01f;
const	float three_over_two_pi  = glm::three_over_two_pi<glm::float_t>();
const	float pi = glm::pi<glm::float_t>();

/*
// стиль движения/состояние персонажа
// лежать, сидеть, стоять, красться, идти, бежать, лететь, карабкаться
enum Rods { LIE, SIT, STAND, CREEP, WALK, RUN, FLY, CLIMB };
*/

// направление и вид движения (6 векторов)
struct Moving {
	int x = 0;
	int y = 0;
	int z = 0;
	float a = three_over_two_pi;	// азимут ( 0 - направление оси X)
	float t = 0.0f;               // тангаж ( 0 -горизонталь, пи/2 -вертикаль)
	float r = 0.0;
};

// список событий окна
enum WindowEvents { NO_EVENTS, CLOSE, MOVE, RESIZE, FOCUS_ON, FOCUS_OFF,
	FULLSCREEN_ON, FULLSCREEN_OFF };

// список событий взаимодействия с пользователем
enum KeysEvents { KEY_UP, KEY_DOWN, MOUSE_UP, MOUSE_DOWN, MOUSE_MOVE };

// действия пользователя в окне
struct ActionsUser {
	const Uint8 * keys; // массив состояния клавиатуры (SDL2)
	Uint32 btns;			  // маска нажатых кнопок мыши
	int x;    // координата X курсора мыши
	int y;    // координата Y курсора мыши
};

////////
//  Отрисовка контента 3D средствами GLSL шейдерной программы
//
class Content3D
{
	private:
		float win_aspect = 1.0f;
		Conf_Content * cfg = nullptr;
		lib::GLSLProgram * prog = nullptr;

		// направление наверх
		glm::vec3 upward = glm::vec3(0.0, 1.0, 0.0);
		// матрица модели
		glm::mat4 model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0, 0.0, 0.0));

		// точка размещения камеры
		glm::vec3 look_fr = glm::vec3(0.0f, 0.0f, 4.0f);
		// направление взгляда
		glm::vec3 look_to = glm::vec3(0.0f, 0.0f, 0.0f);
		
		//TODO: перенести это в модуль интерфейса
		float speed = 0.1f;
		float sensitivity = 1.0f;

		// начальный загрузчик пространства
		short load_space();
		// динамическое изменение картинки (вида из камеры)
		void make_view(glm::vec3 looking, glm::vec3 moving);
		// модуль деструктора
		void free_resources(void);

		// блокировка дубликатов
		Content3D(const Content3D &);
		Content3D operator=(const Content3D &);

	public:
		std::string err = "";

		Content3D(void) {};
		~Content3D(void);
		void rendering(glm::vec3 looking, glm::vec3 moving);
		bool init(Conf_Content *);
		void resize_viewport(int width_px, int height_px);
};

} //namespace app
#endif //__CONTENT3D_H__
