//----------------------------------------------------------------------------
//
// file: main.cpp
//
// Пример использования функции OpenGL 3.3 core 
//
//----------------------------------------------------------------------------
#include "tools.hpp"
#include "ttf.hpp"

int
	win_w = TR_WINDOW_WIDTH,
	win_h = TR_WINDOW_HEIGHT;

//## Создание и заполнение буферов GPU
//
void create_content(void)
{
	GLuint Vao = 0;
	glGenVertexArrays(1, &Vao);
	glBindVertexArray(Vao);

	// Плоский прямоугольник на все окно
	GLfloat v_position[] = {
		-1.f, -1.f,
     1.f, -1.f,
    -1.f,  1.f,
     1.f,  1.f,
    };

	GLuint vertVbo = 0;
	glGenBuffers(1, &vertVbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_position), v_position, GL_STATIC_DRAW);
	GLint vertex_position = glGetAttribLocation(shaderProgram, "vertex_position");
	glVertexAttribPointer(vertex_position, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vertex_position);

	// Координаты текстуры
	GLfloat t_position[] = {
		0.f, 0.f,
    1.f, 0.f,
    0.f, 1.f,
    1.f, 1.f,
	};

	GLuint texVbo = 0;
	glGenBuffers(1, &texVbo);
	glBindBuffer(GL_ARRAY_BUFFER, texVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_position), t_position, GL_STATIC_DRAW);

	GLint texure_position = glGetAttribLocation(shaderProgram, "texure_position");
	glVertexAttribPointer(texure_position, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(texure_position);

	glActiveTexture(GL_TEXTURE0);
	GLuint hd_image[1];
	glGenTextures(1, hd_image);
	glBindTexture(GL_TEXTURE_2D, hd_image[0]);
	
	// Избражение текстуры
	pngImg image0 = get_png_img( "texture.png" );

	TTF ttf { TR_FONT_FNAME, 56 };
	std::wstring eString { L"Байкал-2017." };
	ttf.load_chars( eString );
	ttf.set_cursor( 10, 10 );
	ttf.set_color( 0x10, 0x10, 0xE0 );
	ttf.write_wstring( image0, eString );

	GLint level_of_details = 0, frame = 0;
	glTexImage2D(GL_TEXTURE_2D, level_of_details, GL_RGBA,
		image0.w, image0.h,	frame, GL_RGBA, GL_UNSIGNED_BYTE, image0.img.data());
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 
	GLint sampler0 = glGetUniformLocation(shaderProgram, "image0");
	if(0 > sampler0) ERR("Not found uniform name image0\n");
  glUniform1i(sampler0, 0);
	
	return;
}

//## Главный цикл приложения
//
void run_application(GLFWwindow *window)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.6f, 0.7f, 1.0f, 1.f);

	// Показать результат
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return;
}

//## Точка входа
//
int main()
{	
	setlocale(LC_ALL, "rus"); // даже не знаю, надо-ли это.
	try	{
		GLFWwindow *window = init_opengl();
		create_content();
		run_application(window);
		glfwDestroyWindow(window);
	}	catch(std::exception & e) {
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::cout << "FAILURE: undefined exception.\n";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

