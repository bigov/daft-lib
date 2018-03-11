//----------------------------------------------------------------------------
//
// file: main.cpp
//
// Раздельные буферы для каждого атрибута (по 4 точки на прямоугольник) 
// + индексный буфер из 6 значений для их обхода.
//
//----------------------------------------------------------------------------
#include "tools.hpp"
#include "texture.hpp"
#define GLM_FORCE_RADIANS

// VBO массив из 6 точек для создания прямоугольника из 2-х треугольников:
// 4 координаты 3D, 4 значения цвета RGBA, 4 координаты нормали, UV - текстуры
GLfloat pos3d[] = {
  -0.49f, 0.0f,  0.49f, 1.0f,
   0.49f, 0.0f,  0.49f, 1.0f,
   0.49f, 0.0f, -0.49f, 1.0f,
  -0.49f, 0.0f, -0.49f, 1.0f,
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
	0.1875f, 0.1875f,
	0.1250f, 0.1875f,
};

GLuint idx[] = { 0, 1, 2, 2, 3, 0 };

float x_i = 500.f;
float z_i = 500.f;

GLuint vao      = 0,
	vbo_pos3d     = 0,
	vbo_color     = 0,
	vbo_normal    = 0,
	vbo_tex2d     = 0,
	vbo_id        = 0,
	render_points = 0;

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
	pos3d[0]  = x - 0.45f; pos3d[2]  = z + 0.45f;
	pos3d[4]  = x + 0.45f; pos3d[6]  = z + 0.45f;
	pos3d[8]  = x + 0.45f; pos3d[10] = z - 0.45f;
	pos3d[12] = x - 0.45f; pos3d[14] = z - 0.45f;
	return;
}

//## заполнение буфера данными
//
void fill_buffers()
{
	size_t size3d = sizeof(pos3d);
	size_t size2d = sizeof(tex2d);

	size_t p3d = 0;
	size_t p2d = 0;
	
	size_t count_idx = sizeof(idx);
	size_t pos_id = 0;

	// обход от -_i до +_i
	for (float z = 0.f - z_i; z < z_i; z += 1.0f)
	for (float x = 0.f - x_i; x < x_i; x += 1.0f)
	{
		setup_quad(x, z);
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo_pos3d);
		glBufferSubData(GL_ARRAY_BUFFER, p3d, size3d, pos3d);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
		glBufferSubData(GL_ARRAY_BUFFER, p3d, size3d, color);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
		glBufferSubData(GL_ARRAY_BUFFER, p3d, size3d, normal);

		p3d += size3d;

		glBindBuffer(GL_ARRAY_BUFFER, vbo_tex2d);
		glBufferSubData(GL_ARRAY_BUFFER, p2d, size2d, tex2d);

		p2d += size2d;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, pos_id, count_idx, idx);
		pos_id += count_idx;
		for (auto i = 0; i < 6; ++i) idx[i] += 4;

		render_points += 6;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	return;
}

void start_application(void)
{
	auto t_start = std::chrono::high_resolution_clock::now();
	glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
	init_texture_buffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Вычисление размера буфера
	auto bufsize = sizeof(float) * 4 *
		static_cast<size_t>(x_i) * static_cast<size_t>(z_i);

	glGenBuffers(1, &vbo_pos3d);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pos3d);
	glBufferData(GL_ARRAY_BUFFER, 24 * bufsize, 0, GL_STATIC_DRAW);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "pos3d");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, 24 * bufsize, 0, GL_STATIC_DRAW);
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, 24 * bufsize, 0, GL_STATIC_DRAW);
	GLint norAttrib = glGetAttribLocation(shaderProgram, "normal");
	glEnableVertexAttribArray(norAttrib);
	glVertexAttribPointer(norAttrib, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	glGenBuffers(1, &vbo_tex2d);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_tex2d);
	glBufferData(GL_ARRAY_BUFFER, 12 * bufsize, 0, GL_STATIC_DRAW);
	GLint texAttrib = glGetAttribLocation(shaderProgram, "tex2d");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Выделить память под индексный буфер
	glGenBuffers(1, &vbo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * bufsize, 0, GL_STATIC_DRAW);

	// заполнить буфер данными
	fill_buffers();

	glm::vec3 vecUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.4f, 1.0f), vecUp
	);
	
	glm::mat4 proj = glm::perspective(1.18f, 8.0f / 6.0f, 0.1f, 1000.0f);
	//glm::mat4 proj = glm::perspective(64.0f, 8.0f / 6.0f, 0.1f, 5000.0f);
	GLint uniMvp = glGetUniformLocation(shaderProgram, "mvp");

	//----------------------------------------------------------------------------
	glDisable(GL_CULL_FACE);
  glm::mat4 model {};
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
    glm::mat4 mvp = proj * view * model;
    glUniformMatrix4fv(uniMvp, 1, GL_FALSE, &mvp[0][0]);// glm::value_ptr(proj * view * model));
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, render_points, GL_UNSIGNED_INT, NULL);
		
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
