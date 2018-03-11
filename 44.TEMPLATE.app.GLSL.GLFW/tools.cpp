//----------------------------------------------------------------------------
//
// file: tools.cpp
//
// Набор функций, необходимый  для создания контента и компиляции шейдера
// 
//----------------------------------------------------------------------------
#include "tools.hpp"

GLFWwindow * pWin = nullptr;
GLuint shaderProgram = 0;

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
	return content;
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

//### Создание окна
//
void init_opengl_content(void)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) ERR("Error init GLFW lib.");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	pWin = glfwCreateWindow(1024, 800, "OpenGL tests", NULL, NULL);
	if (nullptr == pWin) ERR("Creating Window fail.");
	glfwMakeContextCurrent(pWin);
	if(!ogl_LoadFunctions())	ERR("Can't load OpenGl finctions");
	glfwSwapInterval(0);
	glfwSetKeyCallback(pWin, key_callback);

	init_program();
	return;
}

