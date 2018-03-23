//----------------------------------------------------------------------------
//
// file: main.cpp
//
// Пример использования функции OpenGL 3.3 core 
//
//----------------------------------------------------------------------------
#include <iostream>
#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>
#define ERR throw std::runtime_error
#define GLSL(src) "#version 330 core\n" #src
//----------------------------------------------------------------------------

//### Код вершинного шейдера
const GLchar * vert_shader = GLSL(
	layout (location=0) in vec4 VertexPosition;
	layout (location=1) in vec3 VertexColor;

	out vec3 FrColor;

	void main() {
		FrColor	= VertexColor;
		gl_Position = VertexPosition;
	}
);

//### Код фрагментного шейдера
const GLchar * frag_shader = GLSL(
	in vec3 FrColor;
	out vec3 Color;

	void main() {
  	Color = FrColor;
	}
);

GLFWwindow * pWin = nullptr;
GLuint hdl_VAO = 0;
GLuint pos_Buf = 0;
GLuint col_Buf = 0;

//### GLFW обработчик ошибок
void error_callback(int error, const char* description)
{
	std::cout << "GLFW error " << error << ": " << description;
	return;
}

//### GLFW обработчик клавиатуры
void key_callback(GLFWwindow* window, int key, int sc, int ac, int md)
{
	if (md == sc) md = sc; //затычка
	
	if (key == GLFW_KEY_ESCAPE && ac == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, true);
	return;
}

//### Создание окна
void open_window(void)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) ERR("Error init GLFW lib.");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	pWin = glfwCreateWindow(1024, 800, "GLSL learn", NULL, NULL);
	if (nullptr == pWin) ERR("Creating Window fail.");
	glfwMakeContextCurrent(pWin);
	if(!ogl_LoadFunctions())	ERR("Can't load OpenGl finctions");
	glfwSwapInterval(0);
	glfwSetKeyCallback(pWin, key_callback);
	return;
}

//## компиялция шейдера с контролем результата
void compile_shader(GLuint shader)
{
	glCompileShader(shader);
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if(GL_FALSE == result)
	{
		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if(logLen)
		{
			char * log = new char[logLen];
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			std::cout << log << '\n';
			delete [] log;
		}
		ERR("Error compile SHADER");
	}
	return;
}

//### Компиляция и запуск GLSL программы
void init_program(void)
{
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	if (!vertShader) ERR("Error create GL_VERTEX_SHADER");
	glShaderSource(vertShader, 1, &vert_shader, NULL);
	compile_shader(vertShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragShader) ERR("Error create GL_FRAGMENT_SHADER");
	glShaderSource(fragShader, 1, &frag_shader, NULL);
	compile_shader(fragShader);

	GLuint program = glCreateProgram();
	if (!program) ERR("Error creating GLSL program\n");
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (GL_FALSE == status)
	{
		GLint logLen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen)
		{
			char * log = new char[logLen];
			GLsizei written;
			glGetProgramInfoLog(program, logLen, &written, log);
			std::cout << log << '\n';
			delete [] log;
		}
		ERR("Failed to link GLSL program.\n");
	}
	glUseProgram(program);

	return;
}

//### Загрузка данных, установка начальных параметров
//
void init_scene(void)
{
	open_window();
	init_program();

	glClearColor(0.5f, 0.69f, 1.0f, 1.0f);

	float pos_Data[] = {
		-0.8f, -0.8f, 0.0f, 1.0f,
		 0.8f, -0.8f, 0.0f, 1.0f,
		 0.0f,  0.8f, 0.0f, 1.0f,
	};

	float col_Data[] = {
		0.4f, 1.0f, 0.4f,
		0.4f, 1.0f, 0.4f,
		0.4f, 1.0f, 0.4001f,
	};

	glGenVertexArrays(1, &hdl_VAO);
	glBindVertexArray(hdl_VAO);
	
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &pos_Buf);
	glBindBuffer(GL_ARRAY_BUFFER, pos_Buf);
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), pos_Data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glGenBuffers(1, &col_Buf);
	glBindBuffer(GL_ARRAY_BUFFER, col_Buf);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), col_Data, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	glBindVertexArray(0);

	return;
}

//### Отображение контента
void draw_scene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(hdl_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	return;
}

//### Блок управления
void start_application(void)
{
	init_scene();
	while (!glfwWindowShouldClose(pWin))
		{
			draw_scene();
			glfwSwapBuffers(pWin);
			glfwPollEvents();
		}
	 	glfwDestroyWindow(pWin);
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
