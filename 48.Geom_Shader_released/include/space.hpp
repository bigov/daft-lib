//============================================================================
//
// file: space.hpp
//
// Заголовок класса управления пространством 3D сцены
//
//    pY
//    |
//    |_____ pX
//    /
//   /pZ
//
//     7(-+-)~~~~~~~~2(++-)
//    /|            /|
//   / |           / |
//  6(-++)~~~~~~~~3(+++)
//  |  |          |  |
//  |  |          |  |
//  |  4(---)~~~~~|~~1(+--)
//  | /           | /
//  |/            |/
//  5(--+)~~~~~~~~0(+-+)
//
//============================================================================
#ifndef __SPACE_HPP__
#define __SPACE_HPP__

#include "main.hpp"
#include "config.hpp"
#include "glsl.hpp"
#include "t256x256.hpp"
#include "vbo.hpp"

namespace tr
{
	struct rig // описание элемента пространства
	{
		short type = 0; // тип
		char gage = 1;  // размер
		float
			x = 0.f,      // |
			y = 0.f,      // | углы поворота в пространстве вокруг осей x,y,z
			z = 0.f;      // |
 		int msec = 0;   // миллисекунд от начала суток
	};

	extern std::unordered_map<float,
			   std::unordered_map<float,
			   std::unordered_map<float, rig>>> space_map; // карта элементов

	// проверка наличия элемента по указанным координатам
	extern bool space_is_empty(float, float, float);
	extern bool space_is_empty(glm::vec3);

	struct evInput
	{
		float dx, dy; // смещение указателя мыши в активном окне
		int fb, rl, ud,  // управление направлением движения в 3D пространстве
		key_scancode, key_mods, mouse_mods,
		fps; // частота кадров (для коррекции скорости движения)
	};

	const	float pi = glm::pi<glm::float_t>();
	const	float two_pi = glm::two_pi<glm::float_t>();
	const	float half_pi = glm::half_pi<glm::float_t>();
	const	float _half_pi = 0 - half_pi;
	const	float look_up = half_pi - 0.01f;
	const	float look_down = 0 - half_pi + 0.01f;
	const	float three_over_two_pi  = glm::three_over_two_pi<glm::float_t>();

	class Scene
	{
		private:
 			Scene(const tr::Scene&);
			Scene operator=(const tr::Scene&);
			tr::Glsl prog {};

			std::vector<vbo> VBOs {};

			GLuint vao_id = 0; // ID VAO
			GLsizei	count = 0;       // число внесенных в VAO элементов для отображения
			GLsizeiptr points = 0;   // общее количество элементов в сцене

			float
				rl=0.f, ud=0.f, fb=0.f, // скорость движения по направлениям
				look_a =  3.928f, // азимут (0 - X)
				look_t = -0.276f, // тангаж (0 - горизОнталь, пи/2 - вертикаль)
				k_sense = 4.0f,   // TODO: чувствительность через Config
				k_mouse = 0.002f;

			bool load_complete = false; // Загрузка сцены завершена
			glm::mat4 MatView {};
			//glm::vec4 lookDir {}; // напрвление взгляда
			glm::vec3
				ViewFrom {3.f, 4.f, 3.f},
				ViewTo {},
				upward {0.0, 1.0, 0.0}; // направление наверх

			bool element_exist(GLfloat, GLfloat, GLfloat);
			void element_remove(GLfloat, GLfloat, GLfloat);
			void element_update(GLfloat, GLfloat, GLfloat);
			void element_insert(GLfloat, GLfloat, GLfloat);

			void calc_position(const evInput & ev);
			void draw_hud(void);
			void draw_wstring(int x, int y, const std::wstring & ws);
			void space_place(GLfloat, GLfloat, GLfloat);
			void space_generate(void);
			void space_array_fill(void);

		public:
			Scene(void) {};
			~Scene(void) {};

			void init(void);
			void draw(const evInput &);
	};

} //namespace
#endif
