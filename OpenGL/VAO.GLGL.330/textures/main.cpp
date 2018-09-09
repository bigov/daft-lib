//----------------------------------------------------------------------------
//
// file: main.cpp
//
// используется профиль OpenGL 3.3 core 
//
//----------------------------------------------------------------------------
#include "tools.hpp"
#define GLSL(src) "#version 330 core\n" #src
//----------------------------------------------------------------------------

//### Код вершинного шейдера
const GLchar * vert_shader = GLSL(
	layout (location=0) in vec4 VertexPosition;
	layout (location=1) in vec2 TextureCoord;

	out vec2 f_texcoord;
	
	void main() {
		gl_Position = VertexPosition;
		f_texcoord = TextureCoord;
	}
);

//### Код фрагментного шейдера
const GLchar * frag_shader = GLSL(
	in vec2 f_texcoord;
	out vec4 Color;
	uniform sampler2D texture_0;

	void main() {
		vec2 flip_tex = vec2(f_texcoord.x, 1.0 - f_texcoord.y);
		Color = texture2D(texture_0, flip_tex);
	}
);

//### Загрузка данных, установка начальных параметров
GLuint rect_1(void)
{
	float pos_data[] = {
		-0.9f, -0.9f, 0.0f, 1.0f,
		-0.1f, -0.9f, 0.0f, 1.0f,
		-0.1f,  0.9f, 0.0f, 1.0f,

		-0.1f,  0.9f, 0.0f, 1.0f,
		-0.9f,  0.9f, 0.0f, 1.0f,
		-0.9f, -0.9f, 0.0f, 1.0f,
	};

	float tex_data[] = {
		0.125f,  0.125f,  0.1875f, 0.125f,  0.1875f, 0.1875f,
		0.1875f, 0.1875f, 0.125f,  0.1875f, 0.125f,  0.125f
	};

	GLuint hdl_VAO = 0;
	glGenVertexArrays(1, &hdl_VAO);
	glBindVertexArray(hdl_VAO);
	
	glEnableVertexAttribArray(0);
	GLuint pos_buffer = 0;
	glGenBuffers(1, &pos_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
	glBufferData(GL_ARRAY_BUFFER, 24*sizeof(float), pos_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	GLuint tex_buffer = 0;
	glGenBuffers(1, &tex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, tex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), tex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindVertexArray(0);

	return hdl_VAO;
}

//### Загрузка данных, установка начальных параметров
GLuint rect_2(void)
{
	float pos_data[] = {
		0.1f, -0.9f, 0.0f, 1.0f,
		0.9f, -0.9f, 0.0f, 1.0f,
		0.9f,  0.9f, 0.0f, 1.0f,

		0.9f,  0.9f, 0.0f, 1.0f,
		0.1f,  0.9f, 0.0f, 1.0f,
		0.1f, -0.9f, 0.0f, 1.0f,
	};

	GLubyte tex_data[] = {
		30, 30, 45, 30, 45, 45,
		45, 45, 30, 45, 30, 30
	};

	GLuint hdl_VAO = 0;
	glGenVertexArrays(1, &hdl_VAO);
	glBindVertexArray(hdl_VAO);
	
	glEnableVertexAttribArray(0);
	GLuint pos_buffer = 0;
	glGenBuffers(1, &pos_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
	glBufferData(GL_ARRAY_BUFFER, 24*sizeof(float), pos_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	GLuint tex_buffer = 0;
	glGenBuffers(1, &tex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, tex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLubyte), tex_data, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);

	glBindVertexArray(0);

	return hdl_VAO;
}

void init_texture_buffer(void)
{
	GLuint m_textureObj;
	glGenTextures(1, &m_textureObj);
	glActiveTexture(GL_TEXTURE0); // можно загрузить не меньше 48
	glBindTexture(GL_TEXTURE_2D, m_textureObj);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);

	// Установка опций отрисовки текстур
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return;
}


//### Отображение контента
void draw_scene(GLuint VAO, GLsizei count_vertices)
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, count_vertices);
	glBindVertexArray(0);
	return;
}

//### Блок управления
void start_application(void)
{
	GLFWwindow * win = open_window();
	init_program(vert_shader, frag_shader);

	GLuint VAO_1 = rect_1();
	GLuint VAO_2 = rect_2();

	init_texture_buffer();
	while (!glfwWindowShouldClose(win))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			draw_scene(VAO_1, 6);
			draw_scene(VAO_2, 6);
			glfwSwapBuffers(win);
			glfwPollEvents();
		}
	 	glfwDestroyWindow(win);
	return;
}

//###
int main()
{
	try	{ 
		start_application(); 
	}	catch(std::exception & e) {
		std::cout << e.what() << '\n';;
		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::cout << "FAILURE: undefined exception.\n";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
