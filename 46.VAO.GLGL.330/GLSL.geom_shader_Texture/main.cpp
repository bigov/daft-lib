//----------------------------------------------------------------------------
//
// file: main.cpp
//
// Пример использования функции OpenGL 3.3 core 
//
//----------------------------------------------------------------------------
#include "tools.hpp"

void start_application(void)
{
	glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
	glm::vec3 toUp(0.f, 1.f, 0.f);

//----------------------------------------------------------------------------
    // Create VBO with point coordinates
    GLuint vbo;
    glGenBuffers(1, &vbo);

//////////////////////

		GLuint texture_id;
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Загрузка текстуры
		tr::pngImg texture = tr::get_png_img("tex0.png.");
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.w, texture.h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, texture.d());
		glGenerateMipmap(GL_TEXTURE_2D);
		
		//glBindTexture(GL_TEXTURE_2D, 0);

//////////////////////

    GLfloat points[] = {
    	// Coordinates        Color
        0.f, 0.f, 0.f,      1.0f, 1.0f, 0.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Create VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Specify layout of point data
    GLuint posAttrib = get_attrib_location("pos");
    
		glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
			6 * sizeof(GLfloat), 0);

    //glEnableVertexAttribArray(colAttrib);
    //glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
		//	6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));

    // Set up transformation matrices
		GLint uniMVP = get_uniform_location("MVP");

		glm::mat4
			model {1},
			view = glm::lookAt(glm::vec3(0.0f, 0.4f, 1.3f), 
				glm::vec3(0.0f, 0.0f, 0.0f), toUp),
			proj = glm::perspective(glm::radians(45.0f), 8.0f / 6.0f, 0.1f, 10.0f),
			MVP {};

	glDisable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
 	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE);


//----------------------------------------------------------------------------
	std::chrono::seconds oneSec(1);
  std::chrono::time_point<std::chrono::system_clock> t_start, t_now;
	t_start = std::chrono::high_resolution_clock::now();
	int
		fps  = 0,
		fpsT = 5000;

	std::string win_title {};
	while (!glfwWindowShouldClose(pWin))
	{
		fps++;
		t_now = std::chrono::high_resolution_clock::now();
	 	std::chrono::duration<double> fp_ms = t_now - t_start;
		auto time = static_cast<float>(fp_ms.count());
		model *= glm::rotate(0.5f/static_cast<float>(fpsT), glm::vec3(1,1,0));

		MVP = proj * view * model;
		glUniformMatrix4fv(uniMVP, 1, GL_FALSE, glm::value_ptr(MVP));

		if(time >= 1)
		{
			t_start = std::chrono::high_resolution_clock::now();
			fpsT = fps;
			fps = 0;
		}
		win_title = "FPS: " + std::to_string(fpsT);
		glfwSetWindowTitle(pWin, win_title.c_str());

      // Render frame 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_POINTS, 0, 1);
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
