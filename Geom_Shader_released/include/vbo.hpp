//============================================================================
//
// file: vbo.cpp
//
// Class GLSL VBOs control
//
//============================================================================
#ifndef __VBO_HPP__
#define __VBO_HPP__

#include "main.hpp"
#include "config.hpp"

namespace tr {

class vbo {
	public:
		GLint n;       // количество чисел в атрибуте
		GLenum type;   // индекс типа данных OpenGL
		GLuint attrib; // индекс GLSL атрибута

		GLuint id           = 0; // индекс буфера VBO
		GLsizeiptr el_size  = 0; // число байт для хранения одного элемента
		GLsizeiptr amount   = 0; // число байт, переданных в VBO буфер GPU
		GLsizeiptr capacity = 0; // зарезервированный размер буфера
		float cache[5]; // кэш для передачи данных из внешней функции

		vbo(GLint digits_on_attribute, GLenum gl_enum_type,
			GLuint attrib_id, void (*_fn_get_data)(const float*, float*)
		);
		vbo& operator=(const vbo& other) = default;


		void allocate_mem(GLsizeiptr count_of_elements);
		void SubData(const float* data);

	private:
		// Адрес функции преобразования данных для заполнения элемента массива VBO
		void (*get_data)(const float*, float*);
};

} //tr
#endif

