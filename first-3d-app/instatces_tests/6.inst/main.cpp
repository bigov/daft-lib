//----------------------------------------------------------------------------
//
// file: main.cpp
//
// - Раздельные буферы для каждого атрибута
// - Инстанцирование координат вершин
//
//----------------------------------------------------------------------------
#include "tools.hpp"
#include "texture.hpp"

// VBO массив из 6 точек для создания прямоугольника из 2-х треугольников:
// 4 координаты 3D, 4 значения цвета RGBA, 4 координаты нормали, UV - текстуры
GLfloat pos3d[] = {
  -0.49f, 0.0f, -0.49f, 1.0f,
   0.49f, 0.0f, -0.49f, 1.0f,
  -0.49f, 0.0f,  0.49f, 1.0f,
   0.49f, 0.0f,  0.49f, 1.0f,
};

GLfloat color[] = {
	0.6f, 0.9f, 0.6f, 1.0f,
	0.6f, 0.9f, 0.6f, 1.0f,
	0.6f, 0.9f, 0.6f, 1.0f,
	0.6f, 0.9f, 0.6f, 1.0f,
};

GLfloat normal[] = {
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
};

GLfloat tex2d[] = {
	0.1250f, 0.1250f,
	0.1875f, 0.1250f,
	0.1250f, 0.1875f,
	0.1875f, 0.1875f,
};

float x_i = 500.f;
float z_i = 500.f;

GLuint vao   = 0,
	vbo_pos3d  = 0,
	vbo_color  = 0,
	vbo_normal = 0,
	vbo_tex2d  = 0,
	vbo_orig   = 0,
	instances  = 0;

//## Настройка текстурного буфера
//
void init_texture_buffer(void)
{
	GLuint m_textureObj;
	glGenTextures(1, &m_textureObj);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureObj);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);

	// Установка опций отрисовки текстур
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return;
}

//## заполнение буфера положений
//
void fill_buffers()
{
	GLfloat origin[] = {0.0f, 0.0f, 0.0f, 0.0f};
	size_t at = 0, osize = sizeof(origin);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_orig);

	for (float z = 0.f - z_i; z < z_i; z += 1.0f)
	for (float x = 0.f - x_i; x < x_i; x += 1.0f)
	{
		origin[0] = x; origin[2] = z;
		glBufferSubData(GL_ARRAY_BUFFER, at, osize, origin);
		at += osize;
		++instances;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return;
}

void start_application(void)
{
	auto t_start = std::chrono::high_resolution_clock::now();
	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
	init_texture_buffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Вычисление размера буфера положений экземпляров
	auto origins_size = 4 * sizeof(float) *
		static_cast<size_t>(x_i) * 2 * static_cast<size_t>(z_i) * 2;
	glGenBuffers(1, &vbo_orig);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_orig);
	glBufferData(GL_ARRAY_BUFFER, origins_size, 0, GL_STATIC_DRAW);
	GLint origAttrib = glGetAttribLocation(shaderProgram, "origin");
	glVertexAttribPointer(origAttrib, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(origAttrib);
	glVertexAttribDivisor(origAttrib, 1);

	glGenBuffers(1, &vbo_pos3d);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pos3d);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos3d), pos3d, GL_STATIC_DRAW);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "pos3d");
	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(posAttrib);
	
	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(colAttrib);

	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normal), normal, GL_STATIC_DRAW);
	GLint norAttrib = glGetAttribLocation(shaderProgram, "normal");
	glVertexAttribPointer(norAttrib, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(norAttrib);

	glGenBuffers(1, &vbo_tex2d);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tex2d);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex2d), tex2d, GL_STATIC_DRAW);
	GLint texAttrib = glGetAttribLocation(shaderProgram, "tex2d");
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(texAttrib);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// заполнить буфер данными
	fill_buffers();

	glm::vec3 vecUp = {0.0f, 1.0f, 0.0f};
	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.6f, 1.0f), vecUp
	);
	
	glm::mat4 proj = glm::perspective(glm::radians(64.0f), 800.0f / 600.0f, 0.1f, 5000.0f);
	GLint uniMvp = glGetUniformLocation(shaderProgram, "mvp");

	//----------------------------------------------------------------------------
	glDisable(GL_CULL_FACE);
  glm::mat4 model = {};
	int fps = 0;

  float time = 0.f, dTime = 0.f;
	auto t_now = std::chrono::high_resolution_clock::now();
	std::string win_title = "FPS: ";

	while (!glfwWindowShouldClose(pWin))
	{
		t_now = std::chrono::high_resolution_clock::now();
		dTime = std::chrono::duration_cast<std::chrono::duration<float>>
				(t_now - t_start).count();
		time += dTime; // для расчета FPS
		t_start = t_now;
    
		model = glm::rotate(model, 0.2f * dTime, vecUp);
    glUniformMatrix4fv(uniMvp, 1, GL_FALSE, glm::value_ptr(proj * view * model));
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, instances);
		glfwSwapBuffers(pWin);
		glfwPollEvents();
		
		++fps;
		if (time >= 1.0f)
		{
			glfwSetWindowTitle(pWin, (win_title + std::to_string(fps)).c_str());
			fps = 0;
			time = 0.f;
		}
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
