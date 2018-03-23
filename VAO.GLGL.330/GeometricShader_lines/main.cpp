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
GLFWwindow * pWin = nullptr;
GLuint shaderProgram = 0;

//### Код вершинного шейдера
const GLchar * vert_shader = GLSL(
    in vec2 pos;
    in vec3 color;
    in float sides;

    out vec3 vColor;
    out float vSides;

    void main()
    {
        gl_Position = vec4(pos, 0.0, 1.0);
        vColor = color;
        vSides = sides;
    }
);

//### Код фрагментного шейдера
const GLchar * frag_shader = GLSL(
  in vec3 fColor;
	out vec4 outColor;

  void main()
  {
  	outColor = vec4(fColor, 1.0);
  }
);

//### Код геометрического шейдера
const GLchar * geom_shader = GLSL (
    layout(points) in;
    layout(line_strip, max_vertices = 64) out;

    in vec3 vColor[];
    in float vSides[];
    out vec3 fColor;

    const float PI = 3.1415926;

    void main()
    {
        fColor = vColor[0];

        // Safe, GLfloats can represent small integers exactly
        for (int i = 0; i <= vSides[0]; i++) {
            // Angle between each side in radians
            float ang = PI * 2.0 / vSides[0] * i;

            // Offset from center of point (0.3 to accomodate for aspect ratio)
            vec4 offset = vec4(cos(ang) * 0.3, -sin(ang) * 0.4, 0.0, 0.0);
            gl_Position = gl_in[0].gl_Position + offset;

            EmitVertex();
        }

        EndPrimitive();
    }
);

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

	GLuint geomShader = glCreateShader(GL_GEOMETRY_SHADER);
	if (!geomShader) ERR("Error create GL_GEOMETRY_SHADER");
	glShaderSource(geomShader, 1, &geom_shader, NULL);
	compile_shader(geomShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragShader) ERR("Error create GL_FRAGMENT_SHADER");
	glShaderSource(fragShader, 1, &frag_shader, NULL);
	compile_shader(fragShader);

	shaderProgram = glCreateProgram();
	if (!shaderProgram) ERR("Error creating GLSL program\n");
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, geomShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);
	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (GL_FALSE == status)
	{
		GLint logLen;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen)
		{
			char * log = new char[logLen];
			GLsizei written;
			glGetProgramInfoLog(shaderProgram, logLen, &written, log);
			std::cout << log << '\n';
			delete [] log;
		}
		ERR("Failed to link GLSL program.\n");
	}
	glUseProgram(shaderProgram);

	return;
}

//### Загрузка данных, установка начальных параметров
void init_scene(void)
{
	open_window();
	init_program();

	//glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	return;
}

//### Отображение контента
void draw_scene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, 4);
	return;
}

//### Блок управления
void start_application(void)
{
	init_scene();
//----------------------------------------------------------------------------
    // Create VBO with point coordinates
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat points[] = {
    //  Coordinates     Color             Sides
        -0.45f,  0.45f, 1.0f, 0.0f, 0.0f,  4.0f,
         0.45f,  0.45f, 0.0f, 1.0f, 0.0f,  8.0f,
         0.45f, -0.45f, 0.0f, 0.0f, 1.0f, 16.0f,
        -0.45f, -0.45f, 1.0f, 1.0f, 0.0f, 32.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Create VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat)));

    GLint sidesAttrib = glGetAttribLocation(shaderProgram, "sides");
    glEnableVertexAttribArray(sidesAttrib);
    glVertexAttribPointer(sidesAttrib, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) (5 * sizeof(GLfloat)));

//----------------------------------------------------------------------------
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
