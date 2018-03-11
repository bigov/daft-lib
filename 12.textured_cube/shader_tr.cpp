#include "rigs.hpp"
using namespace std;

/**
 * Считывание шейдерной программы из файла
 */
char* file_read(const char* filename)
{
	Sint64 fsize, nb_read_total = 0, nb_read = 1;

	SDL_RWops* file = SDL_RWFromFile(filename, "rb");
	if (file == NULL) return NULL;
	fsize = SDL_RWsize(file);
	char* content = (char*)malloc(fsize + 1);
	char* buf = content;

	while (nb_read_total < fsize && nb_read != 0){
		nb_read = SDL_RWread(file, buf, 1, (fsize - nb_read_total));
		nb_read_total += nb_read;
		buf += nb_read;
	}
	SDL_RWclose(file);
	if (nb_read_total != fsize){
		free(content);
		return NULL;
	}
	content[nb_read_total] = '\0';
	return content;
}

/**
 * Регистратор сообщений компиляции шейдерной программы
 */
void print_log(GLuint object)
{
	GLint log_length = 0;
	if (gl::IsShader(object)) {
		gl::GetShaderiv(object, gl::INFO_LOG_LENGTH, &log_length);
	} else if (gl::IsProgram(object)) {
		gl::GetProgramiv(object, gl::INFO_LOG_LENGTH, &log_length);
	} else {
		cerr << "printlog: Not a shader or a program." << endl;
		return;
	}
	char* log = (char*)malloc(log_length);

	if (gl::IsShader(object))
		gl::GetShaderInfoLog(object, log_length, NULL, log);
	else if (gl::IsProgram(object))
		gl::GetProgramInfoLog(object, log_length, NULL, log);

	cerr << log << endl;
	free(log);
	return;
}

/**
 * Компиляция шейдеров из файла с перехватом и отображением ошибок
 */
GLuint create_shader(const char* filename, GLenum type)
{
	GLint compile_ok = false;
	const char* versionGLSL;
	int profile;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
	if (profile == SDL_GL_CONTEXT_PROFILE_ES)
		versionGLSL = "#version 100\n";  // OpenGL ES 2.0
	else
		versionGLSL = "#version 130\n";  // OpenGL 3.0

	const GLchar* source = file_read(filename);
	if (source == NULL){
		cerr << "Error open " << filename << SDL_GetError() << endl;
		return 0;
	}
	GLuint res = gl::CreateShader(type);

	const GLchar* sources[] = { versionGLSL, source };
	gl::ShaderSource(res, 2, sources, NULL);
	free((void*)source);

	gl::CompileShader(res);
	gl::GetShaderiv(res, gl::COMPILE_STATUS, &compile_ok);
	if (compile_ok == false) {
		cerr << "Error compile " << filename << endl;
		print_log(res);
		gl::DeleteShader(res);
		return 0;
	}
	return res;
}

