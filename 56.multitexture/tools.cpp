//-----------------------------------------------------------------------------
//
// file: tools.cpp
//
// Набор функций, необходимый  для создания контента и компиляции шейдера
// 
//-----------------------------------------------------------------------------
#include "tools.hpp"

GLuint shaderProgram = 0;

//## Чтение файла в формате PNG
//
pngImg get_png_img(const std::string & f_n)
{
	#if not defined PNG_SIMPLIFIED_READ_SUPPORTED
	ERR("FAILURE: you must update the \"libpng\".");
	#endif

	const char * filename = f_n.c_str();
	png_image info;
  memset(&info, 0, sizeof info);
  info.version = PNG_IMAGE_VERSION;
	if (!png_image_begin_read_from_file(&info, filename))
  	ERR("Can't read PNG image file");

	info.format = PNG_FORMAT_RGBA;
  pngImg res = {
  	static_cast<int>(info.width),
    static_cast<int>(info.height),
    std::vector<unsigned char>(PNG_IMAGE_SIZE(info), '\0')
	};

	if (!png_image_finish_read(&info, NULL, res.img.data(), 0, NULL ))
  {
  	png_image_free(&info);
    ERR(info.message);
  }
  return res;
}

//## Сохранение одноканального изображения строки в файл PNG
//
void savePNG(uint8_t *image, int32_t width, int32_t height)
{
    // Файл для сохранения картинки
    FILE *f = fopen("output.png", "wb");
    png_structp png_ptr =
        png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, f);

    // Изображение в формате RGBA по 8 бит на 
    // канал и по четыре канала на пиксель
    png_set_IHDR(
        png_ptr, 
        info_ptr, 
        width, 
        height, 
        8, 
        PNG_COLOR_TYPE_RGBA, 
        PNG_INTERLACE_NONE, 
        PNG_COMPRESSION_TYPE_BASE, 
        PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    // Одна строка в формате RGBA, 4 канала
    std::vector<uint8_t> row(width * 4);

    // Сохраняем PNG построчно
    for (int32_t y = 0; y < height; ++y)
    {
        // Преобразуем нашу строку из одноканальной в формат RGBA
        for (int32_t x = 0; x < width; ++x)
        {
            // Цвет одинаковый для всех пикселей 0x202020
            row[x * 4 + 0] = 0x20;
            row[x * 4 + 1] = 0x20;
            row[x * 4 + 2] = 0x20;
            // Прозрачность берём из исходных данных
            row[x * 4 + 3] = image[y * width + x];
        }

        // Сохраняем строку в PNG
        png_write_row(png_ptr, row.data());
    }
 
    png_write_end(png_ptr, 0);    
 
    // Закончили работу, освобождаем ресурсы
    fclose(f);
    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    png_destroy_write_struct(&png_ptr, 0);
		return;
}

//## Поддержка работы с TTF
//
FT_Glyph getGlyph(FT_Face face, uint32_t charcode)
{
    // Загрузка глифа в face->glyph с отрисовкой
    FT_Load_Char(face, charcode, FT_LOAD_RENDER);
 
    FT_Glyph glyph = 0;
    // Получаем глиф
    FT_Get_Glyph(face->glyph, &glyph);
    return glyph;
}

//## Поддержка работы с TTF
//
FT_Pos getKerning(FT_Face face, uint32_t leftCharcode, uint32_t rightCharcode)
{
    // Получаем индекс левого символа
    FT_UInt leftIndex = FT_Get_Char_Index(face, leftCharcode);
    // Получаем индекс правого символа
    FT_UInt rightIndex = FT_Get_Char_Index(face, rightCharcode);
 
    // Здесь будет хранится кернинг в формате 26.6
    FT_Vector delta;
    // Получаем кернинг для двух символов
    FT_Get_Kerning(face, leftIndex, rightIndex, FT_KERNING_DEFAULT, &delta);
    return delta.x;
}


//## Чтение содержимого текстового файла
//
// ВНИМАНИЕ!
// Считывается содержимое только UNIX файлов (перевод строки)
//
std::vector<char> get_txt_chars(const std::string & fname)
{
	// проверка наличия файла
	struct stat buffer;
	if (stat (fname.c_str(), &buffer) != 0) ERR("Missing file: " + fname);

	// чтение файла
	std::ifstream file(fname, std::ios::in|std::ios::ate);
	file.exceptions(std::ios_base::badbit|std::ios_base::failbit);
	if (!file.is_open()) ERR("Can't open " + fname);
	auto size = static_cast<long long>(file.tellg());
	std::vector<char> content (static_cast<size_t>(size + 1), '\0');
	file.seekg(0, std::ios::beg);
	file.read(content.data(), size);
	file.close();
	return std::move(content);
}

//## GLFW обработчик ошибок GLFW окна
//
void error_callback(int n, const char* descr)
{
	ERR(std::string("\n[GLFW] error "+std::to_string(n)+": "+descr+'\n'));
	return;
}

//## GLFW обработчик клавиатуры
//
void key_callback(GLFWwindow* window, int key, int sc, int ac, int md)
{
	if (md != sc) md = sc; //!!!TODO!!! затычка
	if (key == GLFW_KEY_ESCAPE && ac == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, true);
	return;
}

//## компиялция шейдера с контролем результата
//
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
//
void init_program(void)
{
	shaderProgram = glCreateProgram();
	if (!shaderProgram) ERR("Error creating GLSL program\n");

#if defined TR_VERT_SHADER_FNAME
	std::vector<char>	vert = get_txt_chars(TR_VERT_SHADER_FNAME);
	const GLchar *v[] = {vert.data()};
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	if (!vertShader) ERR("Error create GL_VERTEX_SHADER");
	glShaderSource(vertShader, 1, v, NULL);
	compile_shader(vertShader);
	glAttachShader(shaderProgram, vertShader);
#endif

#if defined TR_GEOM_SHADER_FNAME
	std::vector<char>	geom = get_txt_chars(TR_GEOM_SHADER_FNAME);
	const GLchar *g[] = {geom.data()};
	GLuint geomShader = glCreateShader(GL_GEOMETRY_SHADER);
	if (!geomShader) ERR("Error create GL_GEOMETRY_SHADER");
	glShaderSource(geomShader, 1, g, NULL);
	compile_shader(geomShader);
	glAttachShader(shaderProgram, geomShader);
#endif

#if defined TR_FRAG_SHADER_FNAME
	std::vector<char>	frag = get_txt_chars(TR_FRAG_SHADER_FNAME);
	const GLchar *f[] = {frag.data()};
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragShader) ERR("Error create GL_FRAGMENT_SHADER");
	glShaderSource(fragShader, 1, f, NULL);
	compile_shader(fragShader);
	glAttachShader(shaderProgram, fragShader);
#endif

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

//### Инициализация функций OpenGL и создание окна
//
GLFWwindow* init_opengl(void)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) ERR("Error init GLFW lib.");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * pWin = glfwCreateWindow(TR_WINDOW_WIDTH, TR_WINDOW_HEIGHT, "OpenGL tests", NULL, NULL);
	if (nullptr == pWin) ERR("Creating Window fail.");
	glfwMakeContextCurrent(pWin);
	if(!ogl_LoadFunctions())	ERR("Can't load OpenGl finctions");
	glfwSwapInterval(0);
	glfwSetKeyCallback(pWin, key_callback);

	//init_program();

	return pWin;
}

