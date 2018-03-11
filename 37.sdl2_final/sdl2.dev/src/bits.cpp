//============================================================================
//
// file: bits.cpp
//
// Определения элементов построения пространства
//
//============================================================================
#include "bits.hpp"
namespace app {

// добавление: в библиотеке GLM нет такой операции
glm::mat4x2 operator+ (glm::mat4x2 m, glm::vec2 v)
{
	m[0] += v;
	m[1] += v;
	m[2] += v;
	m[3] += v;
	return m;
}

////////
// Конструктор класса
//
Cube::Cube(glm::vec3 point_position, short skin_id)
{
	// пересчет координат элементов в координаты точки,
	// заданной вектором через входной параметр "point_position"
	front.lay += point_position;
	back.lay += point_position;
	top.lay += point_position;
	bottom.lay += point_position;
	left.lay += point_position;
	right.lay += point_position;

	// порядок размещения текстур: колонками по 8 штук снизу вверх -
	// front, back, top, bottom, left, right + два места на карту объема
	// номер колонки в карте (short skin_id) соответствует отдельному материалу
	front.tex += glm::vec2((float)skin_id * 0.125f, 0.0f);
	back.tex = front.tex + texture_mesh_step;
	top.tex = back.tex + texture_mesh_step;
	bottom.tex = top.tex + texture_mesh_step;
	left.tex = bottom.tex + texture_mesh_step;
	right.tex = left.tex + texture_mesh_step;
	
	return;
}

} //app
