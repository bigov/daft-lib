#include <iostream>
#include <string>
#include "gl_core_3_3.hpp"
#include <GLFW/glfw3.h>
#define ERR throw std::runtime_error
#define GL_FALSE false
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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	pWin = glfwCreateWindow(1024, 800, "GLSL learn", NULL, NULL);
	if (nullptr == pWin) ERR("Creating Window fail.");
	glfwMakeContextCurrent(pWin);
	if(!gl::sys::LoadFunctions())	ERR("Can't load OpenGl finctions");
	glfwSwapInterval(0);
	glfwSetKeyCallback(pWin, key_callback);
	return;
}

//## компиялция шейдера с контролем результата
void compile_shader(GLuint shader)
{
	gl::CompileShader(shader);
	GLint result;
	gl::GetShaderiv(shader, gl::COMPILE_STATUS, &result);
	if(GL_FALSE == result)
	{
		GLint logLen;
		gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &logLen);
		if(logLen)
		{
			char * log = new char[logLen];
			GLsizei written;
			gl::GetShaderInfoLog(shader, logLen, &written, log);
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
	GLuint vertShader = gl::CreateShader(gl::VERTEX_SHADER);
	if (!vertShader) ERR("Error create GL_VERTEX_SHADER");
	gl::ShaderSource(vertShader, 1, vert_shader_array, NULL);
	compile_shader(vertShader);

	GLuint fragShader = gl::CreateShader(gl::FRAGMENT_SHADER);
	if (!fragShader) ERR("Error create GL_FRAGMENT_SHADER");
	gl::ShaderSource(fragShader, 1, frag_shader_array, NULL);
	compile_shader(fragShader);

	program = gl::CreateProgram();
	if (!program) ERR("Error creating GLSL program\n");
	gl::AttachShader(program, vertShader);
	gl::AttachShader(program, fragShader);
	gl::LinkProgram(program);
	GLint status;
	gl::GetProgramiv(program, gl::LINK_STATUS, &status);
	if (GL_FALSE == status)
	{
		GLint logLen;
		gl::GetProgramiv(program, gl::INFO_LOG_LENGTH, &logLen);
		if (logLen)
		{
			char * log = new char[logLen];
			GLsizei written;
			gl::GetProgramInfoLog(program, logLen, &written, log);
			std::cout << log << '\n';
			delete [] log;
		}
		ERR("Failed to link GLSL program.\n");
	}
	gl::UseProgram(program);

	return;
}

GLuint attrib_location_get(const char * name )
{
	GLint l = gl::GetAttribLocation(program, name);
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

	gl::ClearColor(0.5f, 0.69f, 1.0f, 1.0f);

	float pos_Data[] = {
		-0.8f, -0.8f, 0.0f,
		 0.8f, -0.8f, 0.0f,
		 0.0f,  0.8f, 0.0f,
	};

	
	//gl::GenVertexArrays(1, &hdl_VAO);
	//gl::BindVertexArray(hdl_VAO);

	//gl::GenBuffers(1, &pos_Buf);
  gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);

	//gl::BindBuffer(gl::ARRAY_BUFFER, pos_Buf);
	position_index = attrib_location_get("VertexPosition");
	gl::EnableVertexAttribArray(position_index);
	gl::VertexAttribPointer(position_index, 3, gl::FLOAT, false, 0, pos_Data);
	
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
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	
	//gl::BindVertexArray(hdl_VAO);
	gl::DrawArrays(gl::TRIANGLES, 0, 3);
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
		std::cout << e.what() << '\n';;
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
