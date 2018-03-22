//----------------------------------------------------------------------------
//
// file: main.cpp
//
// Пример использования функции OpenGL 3.3 core 
//
//----------------------------------------------------------------------------
#include "tools.hpp"

FT_GlyphSlot glyph;
GLuint hd_image[1];
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
	glGenTextures(1, hd_image);

	glBindTexture(GL_TEXTURE_2D, hd_image[0]);
	
	// Избражение текстуры - прозрачный прямоугольник по размеру окна
	std::vector<unsigned char> image0 {};
	image0.assign(win_w * win_h * 4, 0);

	GLint level_of_details = 0, frame = 0;
	glTexImage2D(GL_TEXTURE_2D, level_of_details, GL_RGBA,
		win_w, win_h,	frame, GL_RGBA, GL_UNSIGNED_BYTE, image0.data());
	
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
	// Позиция и размер глифа в строке
	struct Symbol
	{
    int32_t posX;   // Позиция по горизонтали
    int32_t posY;   // Позиция по вертикали (от базовой линии)
    int32_t width;  // Ширина глифа
    int32_t height; // Высота глифа
    FT_Glyph glyph;
	};

	// Инициализация FreeType библиотеки
	FT_Library ftLibrary = 0;
	FT_Init_FreeType(&ftLibrary);

 	// Загрузка шрифта
	FT_Face ftFace = 0;
	FT_New_Face(ftLibrary, TR_FONT_FNAME, 0, &ftFace);

	// Установка размера символа
  FT_UInt pixel_width = 24;
  FT_UInt pixel_height = 0;
	FT_Set_Pixel_Sizes(ftFace, pixel_width, pixel_height);

	// Выводимая строка
	setlocale(LC_ALL, "rus"); // даже не знаю, надо-ли это.
	const std::wstring exampleString {L"Привет на русском языке!"};
	// Массив для хранения используемых символов
	std::vector<Symbol> symbols;
		
	int32_t left = INT_MAX;
	int32_t top = INT_MAX;
	int32_t bottom = INT_MIN;
	uint32_t prevCharcode = 0;
	FT_Pos posX = 0; // Позиция текущего символа в формате 26.6

	// Заполнить массив "symbols" данными всех символов выводимой строки
	for (size_t i = 0; i < exampleString.size(); ++i)
	{
		const uint32_t charcode = exampleString[i];  // Код символа,
		FT_Glyph glyph = getGlyph(ftFace, charcode); // его глиф
		if (!glyph) continue; // Если в шрифте его нет - пропустить TODO: пробел
   	if (prevCharcode)
			posX += getKerning(ftFace, prevCharcode, charcode); // Добавить кернинг
		prevCharcode = charcode;
		symbols.push_back(Symbol{});
    Symbol &symb = symbols.back();
		FT_BitmapGlyph bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(glyph);
		symb.posX = static_cast<int32_t>((posX >> 6) + bitmapGlyph->left);
    // Вертикальная позиция символа относительно базовой линии:
		// отрицательные значения - сверху, положительные - снизу
		symb.posY = -bitmapGlyph->top;
    symb.width = bitmapGlyph->bitmap.width; // Ширина символа
    symb.height = bitmapGlyph->bitmap.rows; // Высота символа
    symb.glyph = glyph;                     // Ссылка на глиф
    // Смещаем позицию текущего символа
    // (glyph->advance имеет формат 16.16, поэтому для приведения 
    // его к формату 26.6 необходимо сдвинуть число на 10 бит враво)
    posX += glyph->advance.x >> 10;
    // Вычисляем самую левую позицию
    left = std::min(left, symb.posX);
    // Вычисляем самую верхнюю позицию
    top = std::min(top, symb.posY);
    // Вычисляем самую нижнюю позицию
    bottom = std::max(bottom, symb.posY + symb.height);
	}
	
	// Смещаем все символы влево, чтобы строка примыкала к левой части
	for (std::size_t i = 0; i < symbols.size(); ++i) symbols[i].posX -= left;

	// Вычисляем размер изображения для выводимой строки
	const Symbol &lastSymbol = symbols.back();
 	// Ширина изображения - правая граница последнего символа в строке
	const int32_t string_width = lastSymbol.posX + lastSymbol.width;
 	const int32_t string_height = bottom - top; // Высота изображения

	// Построить изображение (альфа-канал)
	std::vector<uint8_t> pic_A(string_width * string_height);
	for (std::size_t i = 0; i < symbols.size(); ++i)
	{
    const Symbol &symb = symbols[i];
    FT_BitmapGlyph bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(symb.glyph);
    FT_Bitmap bitmap = bitmapGlyph->bitmap;
 
    for (int32_t srcY = 0; srcY < symb.height; ++srcY)
    {
    	// Координата Y в итоговой картинке
      const int32_t dstY = symb.posY + srcY - top;
      for (int32_t srcX = 0; srcX < symb.width; ++srcX)
      {
       	// Получаем пиксель из изображения символа,
        // (обязательно используйте pitch вместо width)
        const uint8_t c = bitmap.buffer[srcX + srcY * bitmap.pitch];
        if (0 == c) continue; // Если пиксель полностью прозрачный, то пропускаем
 
        // Приводим множество [0..255] к [0..1] для удобства блендинга
        const float a = c / 255.0f;
 
        // Координата X в итоговой картинке
        const int32_t dstX = symb.posX + srcX;
 
        // Вычислим смещение в итоговой картинке
        uint8_t *dst = pic_A.data() + dstX + dstY * string_width;
 
        // Рисуем этот пиксель в итоговую картинку с блендингом
        dst[0] = uint8_t(a * 255 + (1 - a) * dst[0]);
      }
    }
	}

	//Преобразовать в формат RGBA (4 канала)
	uint8_t fg_color = 0xCF;
	uint8_t bg_color = 0x4F;
	double ra = 0.0;
	std::vector<uint8_t> image {};
	for(size_t i = 0; i < pic_A.size(); i++)
	{
		ra = pic_A[i]/255.f;
		
		uint8_t color = static_cast<uint8_t>(
			round(bg_color*(1.f - ra) + fg_color*ra) );

		image.push_back(color);
		image.push_back(10);
		image.push_back(10);
		image.push_back(pic_A[i]);
	}

	glBindTexture(GL_TEXTURE_2D, hd_image[0]);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 10, 14,
		string_width, string_height, 
		GL_RGBA, GL_UNSIGNED_BYTE, image.data());
	
	// освободить ресурсы
	for (std::size_t i = 0; i < symbols.size(); ++i)
    FT_Done_Glyph(symbols[i].glyph);
	FT_Done_Face(ftFace);
	ftFace = 0;
	FT_Done_FreeType(ftLibrary);
	ftLibrary = 0;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
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
	std::cout << '\n';
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

