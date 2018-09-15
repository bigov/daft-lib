#include <iostream>
#include <string>
#include <gl_com_4.5.h>
#include <GLFW/glfw3.h>
#define ERR throw std::runtime_error
//----------------------------------------------------------------------------
const GLchar * vert_shader_array[] = {"#version 430\n\
                                                   \n\
layout (location=0) in vec3 VertexPosition;	       \n\
layout (location=1) in vec3 VertexColor;   	       \n\
												                           \n\
out vec3 FrColor;											             \n\
												                           \n\
void main()						          						       \n\
{                     											       \n\
	FrColor	= VertexColor;   									       \n\
	gl_Position = vec4(VertexPosition, 1.0);	       \n\
}"};//------------------------------------------------------------------------
const GLchar * frag_shader_array[] = {"#version 430\n\
                                                   \n\
in vec3 FrColor;                                   \n\
out vec3 Color;                                    \n\
                                                   \n\
void main()                                        \n\
{                                                  \n\
  Color = FrColor;                                 \n\
}"};//------------------------------------------------------------------------

GLFWwindow* pWin;
GLuint hdl_VAO;
GLuint pos_Buf;
GLuint col_Buf;

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
	if (!glfwInit()) throw std::runtime_error("Error init GLFW lib.");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	pWin = glfwCreateWindow(1024, 800, "GLSL learn", NULL, NULL);
	if (nullptr == pWin) throw std::runtime_error("Creating Window fail.");
	glfwMakeContextCurrent(pWin);
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
void init_scene(void)
{
	open_window();
	init_program();

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glClearColor(0.5f, 0.69f, 1.0f, 1.0f);

	float pos_Data[] = {
		-0.8f, -0.8f, 0.0f,
		 0.8f, -0.8f, 0.0f,
		 0.0f,  0.8f, 0.0f,
	};

	float col_Data[] = {
		0.4f, 1.0f, 0.4f,
		0.4f, 1.0f, 0.4f,
		0.4f, 1.0f, 0.4f,
	};

	glGenVertexArrays(1, &hdl_VAO);
	glBindVertexArray(hdl_VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &pos_Buf);
	glBindBuffer(GL_ARRAY_BUFFER, pos_Buf);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), pos_Data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &col_Buf);
	glBindBuffer(GL_ARRAY_BUFFER, col_Buf);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), col_Data, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);

	return;
}

//### Пример изменения данных, размещенных в графической памяти
void change_gpu_data_array(void)
{
	bool var1 = false;
	if(var1) {
	
	// Вариант 1
	// ---------
	glBindBuffer(GL_ARRAY_BUFFER, col_Buf);
 	GLfloat *data = static_cast<GLfloat*> (
		glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	data[3] = 0.2f;	data[4] = 0.2f;	data[5] = 1.0f;
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, pos_Buf);
 	data = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	data[7] = 0.4f;
	glUnmapBuffer(GL_ARRAY_BUFFER);
	} else {
	
	// Вариант 2
	// Если надо изменить, например, седьмой элемент массива:
	glBindBuffer(GL_ARRAY_BUFFER, pos_Buf);
	GLintptr offset = 7*sizeof(float);
	float pos_SubD[] = {0.0f};
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float), pos_SubD);
	}

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
	try	{ start(); }
	catch(std::exception & e)
	{
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
