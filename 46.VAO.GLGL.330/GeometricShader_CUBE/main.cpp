//----------------------------------------------------------------------------
//
// file: main.cpp
//
// Пример использования функции OpenGL 3.3 core 
//
//----------------------------------------------------------------------------
#include <iostream>
#include <chrono>

#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ERR throw std::runtime_error
#define GLSL(src) "#version 330\n" #src
//----------------------------------------------------------------------------
GLFWwindow * pWin = nullptr;
GLuint shaderProgram = 0;

//### Код вершинного шейдера
const GLchar * vert_shader = GLSL(

    in vec3 pos;
    in vec3 color;

    out vec3 vColor;

    void main()
    {
        gl_Position = vec4(pos, 1.0);
        vColor = color;
    }
);

//### Код геометрического шейдера
const GLchar * geom_shader = GLSL (

    layout(points) in;
    layout(line_strip, max_vertices = 16) out;

		// можно получить ПОВЕХНОСТИ!
    //layout(triangle_strip, max_vertices = 16) out;

    in vec3 vColor[];
    out vec3 fColor;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;

    void main()
    {
        fColor = vColor[0];

        // +X direction is "North", -X direction is "South"
        // +Y direction is "Up",    -Y direction is "Down"
        // +Z direction is "East",  -Z direction is "West"
        //                                     N/S   U/D   E/W
        vec4 NEU = proj * view * model * vec4( 0.1,  0.1,  0.1, 0.0);
        vec4 NED = proj * view * model * vec4( 0.1, -0.1,  0.1, 0.0);
        vec4 NWU = proj * view * model * vec4( 0.1,  0.1, -0.1, 0.0);
        vec4 NWD = proj * view * model * vec4( 0.1, -0.1, -0.1, 0.0);
        vec4 SEU = proj * view * model * vec4(-0.1,  0.1,  0.1, 0.0);
        vec4 SED = proj * view * model * vec4(-0.1, -0.1,  0.1, 0.0);
        vec4 SWU = proj * view * model * vec4(-0.1,  0.1, -0.1, 0.0);
        vec4 SWD = proj * view * model * vec4(-0.1, -0.1, -0.1, 0.0);

				mat4 PVM;
				PVM = mat4(1); // <- если оставить это значение, то будут нарисованы
				               // 4 куба, вращающиеся каждый вокруг своей оси
				PVM = proj * view * model;

        // Create a cube centered on the given point.
        gl_Position = PVM * gl_in[0].gl_Position + NED;
				fColor = vColor[0] * vec3(0.5, 0.5, 0.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NWD;
				fColor = vColor[0] * vec3(0.5, 0.5, 0.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SWD;
				fColor = vColor[0] * vec3(0.5, 0.5, 0.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SED;
				fColor = vColor[0] * vec3(0.5, 0.5, 0.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SEU;
				fColor = vColor[0] * vec3(1.5, 1.5, 1.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SWU;
				fColor = vColor[0] * vec3(1.5, 1.5, 1.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NWU;
				fColor = vColor[0] * vec3(1.5, 1.5, 1.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NEU;
				fColor = vColor[0] * vec3(1.5, 1.5, 1.5);
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NED;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SED;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SEU;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NEU;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NWU;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + NWD;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SWD;
        EmitVertex();

        gl_Position = PVM * gl_in[0].gl_Position + SWU;
        EmitVertex();

        EndPrimitive();
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

	glClearColor(0.3f, 0.49f, 0.8f, 1.0f);
	//glClearColor(0.f, 0.f, 0.f, 1.f);
	return;
}

//### Блок управления
void start_application(void)
{
	auto t_start = std::chrono::high_resolution_clock::now();
	init_scene();
//----------------------------------------------------------------------------
    // Create VBO with point coordinates
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat points[] = {
    //  Coordinates             Color
        -0.45f,  0.45f, -0.45f, 1.0f, 0.0f, 0.0f,
         0.45f,  0.45f, -0.45f, 0.0f, 1.0f, 0.0f,
         0.45f, -0.45f, -0.45f, 0.0f, 0.0f, 1.0f,
        -0.45f, -0.45f, -0.45f, 1.0f, 1.0f, 0.0f,
        -0.45f,  0.45f,  0.45f, 0.0f, 1.0f, 1.0f,
         0.45f,  0.45f,  0.45f, 1.0f, 0.0f, 1.0f,
         0.45f, -0.45f,  0.45f, 1.0f, 0.5f, 0.5f,
        -0.45f, -0.45f,  0.45f, 0.5f, 1.0f, 0.5f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Create VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Specify layout of point data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    // Set up transformation matrices
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");

    glm::mat4 view = glm::lookAt(
        glm::vec3(1.5f, 1.5f, 2.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
 
//----------------------------------------------------------------------------
	while (!glfwWindowShouldClose(pWin))
		{
			glClear(GL_COLOR_BUFFER_BIT);

        // Calculate transformation
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        glm::mat4 model;
        model = glm::rotate(
            model,
            0.25f * time * glm::radians(180.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
        );
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

      // Render frame 
			glDrawArrays(GL_POINTS, 0, 8);
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
