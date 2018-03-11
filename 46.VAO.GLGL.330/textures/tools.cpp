//----------------------------------------------------------------------------
#include "tools.hpp"
//----------------------------------------------------------------------------

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
void init_program(const GLchar * vert_shader, const GLchar * frag_shader)
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
GLFWwindow * open_window(void)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) ERR("Error init GLFW lib.");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * pWin = glfwCreateWindow(1024, 400, "OpenGL test", NULL, NULL);
	if (nullptr == pWin) ERR("Creating Window fail.");
	glfwMakeContextCurrent(pWin);
	if(!ogl_LoadFunctions())	ERR("Can't load OpenGl finctions");
	glfwSwapInterval(0);
	glfwSetKeyCallback(pWin, key_callback);

	//glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
	glClearColor(0.33f, 0.33f, 0.33f, 1.0f);

	return pWin;
}


