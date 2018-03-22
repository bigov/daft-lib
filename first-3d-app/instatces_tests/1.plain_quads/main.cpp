//----------------------------------------------------------------------------
//
// file: main.cpp
//
//	Общий буфер атрибутов без использования индексов
//	
//----------------------------------------------------------------------------
#include "tools.hpp"
#include "texture.hpp"

// VBO массив из 6 точек для создания прямоугольника из 2-х треугольников:
// 4 координаты 3D, 4 значения цвета RGBA, 4 координаты нормали, UV - текстуры
GLfloat points[] = {
//|--pos3d------------------| |--color---------------| |--normal--------------| |--tex2d---------|
  -0.49f, 0.0f, -0.49f, 1.0f,  0.6f, 0.9f, 0.6f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.1250f, 0.1250f,
   0.49f, 0.0f, -0.49f, 1.0f,  0.6f, 0.9f, 0.6f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.1875f, 0.1250f,
   0.49f, 0.0f,  0.49f, 1.0f,  0.6f, 0.9f, 0.6f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.1875f, 0.1875f,
   0.49f, 0.0f,  0.49f, 1.0f,  0.6f, 0.9f, 0.6f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.1875f, 0.1875f,
  -0.49f, 0.0f,  0.49f, 1.0f,  0.6f, 0.9f, 0.6f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.1250f, 0.1875f,
  -0.49f, 0.0f, -0.49f, 1.0f,  0.6f, 0.9f, 0.6f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.1250f, 0.1250f,
};

float x_i = 500.f;
float z_i = 500.f;

GLuint vbo = 0;
GLuint vao = 0;
GLuint render_points = 0;

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

//## Пересчет массива вершин по координатам центральной точки
//
void setup_quad(float x, float z)
{
	points[0]  = x - 0.45f; points[2]  = z - 0.45f;
	points[14] = x + 0.45f; points[16] = z - 0.45f;
	points[28] = x + 0.45f; points[30] = z + 0.45f;
	points[42] = x + 0.45f; points[44] = z + 0.45f;
	points[56] = x - 0.45f; points[58] = z + 0.45f;
	points[70] = x - 0.45f; points[72] = z - 0.45f;
	return;
}

//## заполнение буфера данными
//
void fill_buffer()
{
	size_t count = sizeof(points);
	size_t position = 0;
	
	// обход от -10 до +10
	for (float z = 0.f - z_i; z < z_i; z += 1.0f)
	for (float x = 0.f - x_i; x < x_i; x += 1.0f)
	{
		setup_quad(x, z);
		glBufferSubData(GL_ARRAY_BUFFER, position, count, points);
		position += count;
		render_points += 6;
	}
	return;
}

void start_application(void)
{
	auto t_start = std::chrono::high_resolution_clock::now();
	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Вычисление размера буфера
	auto digits =
		static_cast<size_t>(x_i) * 2 *
		static_cast<size_t>(z_i) * 2 *
		84 * sizeof(float);

	// Выделить память под буфер атрибутов
	glBufferData(GL_ARRAY_BUFFER, digits, 0, GL_STATIC_DRAW);	
	// заполнить буфер данными
	fill_buffer();
	init_texture_buffer();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "pos3d");
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	GLint norAttrib = glGetAttribLocation(shaderProgram, "normal");
	GLint texAttrib = glGetAttribLocation(shaderProgram, "tex2d");

	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(colAttrib);
	glEnableVertexAttribArray(norAttrib);
	glEnableVertexAttribArray(texAttrib);

	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE,
		14 * sizeof(GLfloat), 0);
	
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE,
		14 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));
	
	glVertexAttribPointer(norAttrib, 4, GL_FLOAT, GL_FALSE,
		14 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));

	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
		14 * sizeof(GLfloat), (void*)(12 * sizeof(GLfloat)));

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
		glDrawArrays(GL_TRIANGLES, 0, render_points);
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
