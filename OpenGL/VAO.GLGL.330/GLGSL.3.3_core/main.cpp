#include <iostream>
#include <string>
#include "gl_core33.h"
#include <GLFW/glfw3.h>
#define ERR throw std::runtime_error
//----------------------------------------------------------------------------
const GLchar * vert_shader_array[] = {"#version 330 core\n\
                                                   \n\
layout (location=0) in vec3 VertexPosition;	       \n\
												                           \n\
void main()						          						       \n\
{                     											       \n\
	gl_Position = vec4(VertexPosition, 1.0);	       \n\
}"};
//----------------------------------------------------------------------------
const GLchar * frag_shader_array[] = {"#version 330 core\n\
                                                   \n\
out vec3 color;                                    \n\
                                                   \n\
void main()                                        \n\
{                                                  \n\
  color = vec3(	0.4, 1.0, 0.4);                    \n\
}"};
//----------------------------------------------------------------------------

GLFWwindow * pWin = nullptr;
GLuint 
	hdl_VAO = 0,
	pos_Buf = 0,
	col_Buf = 0,
	program = 0,
	position_index = 0,
	color_index = 0;

//### GLFW обработчик ошибок
void error_callback(int error, const char* description)
{
	std::cout << "GLFW error " << error << ": " << description;
	return;
}

//### GLFW обработчик клавиатуры
void key_callback(GLFWwindow* window, int key, int sc, int ac, int md)
{
	if (md == sc) md = sc; // затычка
	
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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 0);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
  glfwWindowHint(GLFW_VISIBLE, 0);
  const char* title = "GLSL learn";

  pWin = glfwCreateWindow(1024, 800, title, NULL, NULL);
  //fullscreen mode
  //pWin = glfwCreateWindow(1024, 800, title, glfwGetPrimaryMonitor(), NULL);

  //glfwSetWindowPos(pWin, 10, 10);
  glfwShowWindow(pWin);

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
	glShaderSource(vertShader, 1, vert_shader_array, NULL);
	compile_shader(vertShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragShader) ERR("Error create GL_FRAGMENT_SHADER");
	glShaderSource(fragShader, 1, frag_shader_array, NULL);
	compile_shader(fragShader);

	program = glCreateProgram();
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

GLuint attrib_location_get(const char * name )
{
	GLint l = glGetAttribLocation(program, name);
	if(0 > l)
	{
		std::string msg = "Not found attrib name: ";
		msg += name;
		ERR(msg);
	}

  return static_cast<GLuint>( l );
}

//### Загрузка данных, установка начальных параметров
void init_scene(void)
{
	open_window();
	init_program();

	glClearColor(0.5f, 0.69f, 1.0f, 1.0f);

	float pos_Data[] = {
		-0.8f, -0.8f, 0.0f,
		 0.8f, -0.8f, 0.0f,
		 0.0f,  0.8f, 0.0f,
	};

	
	//gl::GenVertexArrays(1, &hdl_VAO);
	//gl::BindVertexArray(hdl_VAO);

	//gl::GenBuffers(1, &pos_Buf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//gl::BindBuffer(gl::ARRAY_BUFFER, pos_Buf);
	position_index = attrib_location_get("VertexPosition");
	glEnableVertexAttribArray(position_index);
	glVertexAttribPointer(position_index, 3, GL_FLOAT, false, 0, pos_Data);
	
	/*
	gl::GenBuffers(1, &pos_Buf);
	//gl::EnableVertexAttribArray(0);
	gl::BindBuffer(gl::ARRAY_BUFFER, pos_Buf);
	gl::BufferData(gl::ARRAY_BUFFER, 9*sizeof(float), pos_Data, gl::STATIC_DRAW);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, GL_FALSE, 0, NULL);
	*/
	/*
	gl::EnableVertexAttribArray(1);
	gl::GenBuffers(1, &col_Buf);
	gl::BindBuffer(gl::ARRAY_BUFFER, col_Buf);
	gl::BufferData(gl::ARRAY_BUFFER, 9*sizeof(float), col_Data, gl::STATIC_DRAW);
	gl::VertexAttribPointer(1, 3, gl::FLOAT, GL_FALSE, 0, NULL);
	*/
	//gl::BindVertexArray(0);
	
	return;
}

//### Отображение контента
void draw_scene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//gl::BindVertexArray(hdl_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//gl::BindVertexArray(0);
	return;
}

//### Блок управления
void start(void)
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
		start();
	}	catch(std::exception & e) {
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::cout << "FAILURE: undefined exception.\n";
		return EXIT_FAILURE;
	}

	std::cout << "\n\nComplete.\n";
	return EXIT_SUCCESS;
}

