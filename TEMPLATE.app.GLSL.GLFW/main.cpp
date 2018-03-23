//----------------------------------------------------------------------------
//
// file: main.cpp
//
// Пример использования функции OpenGL 3.3 core 
//
//----------------------------------------------------------------------------
#include "tools.hpp"

//## Управление работой приложения
//
void start_application(void)
{
	auto t_start = std::chrono::high_resolution_clock::now();
	glClearColor(0.3f, 0.49f, 0.8f, 1.0f);

//----------------------------------------------------------------------------
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

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

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

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

//## Точка входа
//
int main()
{
	try	{
		init_opengl_content();
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

