//============================================================================
//
// file: config.cpp
//
// Управление настройками приложения
//
//============================================================================
#include <iostream>
#include "config.hpp"

namespace tr
{

	// Инициализация статических членов
	GuiParams Config::gui {};
	glm::mat4 MatProjection {}; // матрица проекции 3D сцены
	std::unordered_map<tr::FileDestination, std::string> Config::fp_name {};

	////////
	// Загрузка конфигурации приложения
	//
	void Config::load(void)
	{
		value = 0;
		set_size(800, 600);
		std::string dir = "../assets/";
		fp_name[FONT] = dir + "DejaVuSansMono.ttf";
		//fp_name[TEXTURE] = dir + "256x256.png";
		fp_name[VERT_SHADER] = dir + "vert.glsl";
		fp_name[GEOM_SHADER] = dir + "geom.glsl";
		fp_name[FRAG_SHADER] = dir + "frag.glsl";
		return;
	}

	////////
	// Сохрание настроек
	//
	void Config::save(void)
	{
		return;
	}

	////////
	// Установка соотношения сторон окна
	//
	void Config::set_size(int w, int h)
	{
		gui.w = w;
		gui.h = h;
		if(gui.h > 0)
			gui.aspect = static_cast<float>(gui.w) / static_cast<float>(gui.h);
		else
			gui.aspect = 1.0f;

		// Град   Радиан
		// 45  |  0,7853981633974483
		// 60  |  1,047197551196598
		// 64  |  1,117010721276371
		// 70  |  1,221730476396031
		MatProjection = glm::perspective(1.118f, gui.aspect, 0.01f, 1000.0f);

		return;
	}

	////////
	// Статические методы
	//
	int Config::get_w(void) { return gui.w; }
	int Config::get_h(void) { return gui.h; }
	std::string Config::filepath(tr::FileDestination D) { return fp_name[D]; }

	////////
	// Тестовая функция получения значения
	//
	int Config::get_value(void)
	{
		return value;
	}

} //namespace tr

