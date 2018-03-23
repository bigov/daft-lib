//============================================================================
//
// file: vbo.cpp
//
// Class GLSL VBOs control
//
//============================================================================
#include "vbo.hpp"

namespace tr {

//### конструктор
//
vbo::vbo(GLint N, GLenum T, GLuint A, void (*F)(const float*, float*))
	: n(N), type(T), attrib(A), get_data(F)
{
	GLsizeiptr _sz;

	if(type == GL_FLOAT) _sz = sizeof(GLfloat);
	else if (type == GL_BYTE) _sz = sizeof(GLbyte);
	else if (type == GL_UNSIGNED_BYTE) _sz = sizeof(GLubyte);
	else if (type == GL_SHORT) _sz = sizeof(GLshort);
	else if (type == GL_UNSIGNED_SHORT) _sz = sizeof(GLushort);
	else if (type == GL_INT) _sz = sizeof(GLint);
	else if (type == GL_UNSIGNED_INT) _sz = sizeof(GLuint);
	//else if (type == GL_HALF_FLOAT) ERR("Тип не настроен");
	else if (type == GL_FLOAT) _sz = sizeof(GLfloat);
	else if (type == GL_DOUBLE) _sz = sizeof(GLdouble);
	//else if (type == GL_INT_2_10_10_10_REV) ERR("Тип не настроен");
	//else if (type == GL_UNSIGNED_INT_2_10_10_10_REV) ERR("Тип не настроен");
	else ERR("Неверно указан тип атрибута");

	// число байт, занимаемых одним элементом VBO в памяти GPU
	el_size = _sz * N;

	return;
}

//## зарезервировать память под буфер для размещения elements_count элементов
//
void vbo::allocate_mem(GLsizeiptr elements_count)
{
	glEnableVertexAttribArray(attrib);

	capacity = elements_count * el_size; // резервируемый размер буфера
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, capacity, 0, GL_STATIC_DRAW);

	#ifndef NDEBUG
	assert(elements_count > 0);
	assert(5 > n);
	assert(n > 0);

	GLint _sz = 0;
	// контроль создания буфера
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &_sz);
	assert(capacity == _sz);
	#endif

	// настройка размещения атрибутов
	glVertexAttribPointer(attrib, n, type, GL_FALSE, 0, NULL);
	return;
}

//### Последовательное внесение данных в буфер данных VBO
//
void vbo::SubData(const float* xyz)
{
	// принять данные из внешней функции через кэш
	get_data(xyz, cache);

	glBindBuffer(GL_ARRAY_BUFFER, id);
	#ifndef NDEBUG
	if ((capacity - amount) < el_size) ERR("VBO overflow");
	#endif
	glBufferSubData(GL_ARRAY_BUFFER, amount, el_size, cache);
	amount += el_size;
	return;
}

} //tr
