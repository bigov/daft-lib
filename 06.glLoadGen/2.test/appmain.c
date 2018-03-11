/**
 *
 * Start from 
 *  https://en.wikibooks.org/wiki/OpenGL_Programming
 *
 */

#include <stdio.h>
#include "gl_core_2_1.h"
#include <SDL2/SDL.h>

GLuint program;
GLint attribute_coord2d;

GLuint create_shader(const char* filename, GLenum type);

/**
 * Регистратор ошибок
 * (пока) только печатает информацию на стандартный вывод.
 */
void logErr(const char** s, int n)
{
  int idx = 0;
  while (n > idx) printf("%s", s[idx++]);
  printf("\n\n");
  return;
}

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

  while (nb_read_total < fsize && nb_read != 0)
  {
    nb_read = SDL_RWread(file, buf, 1, (fsize - nb_read_total));
    nb_read_total += nb_read;
    buf += nb_read;
  }
  SDL_RWclose(file);
  if (nb_read_total != fsize)
  {
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

  if (glIsShader(object)) {
    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
  } else if (glIsProgram(object)) {
    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  } else {
    const char* err[1] = {"printlog: Not a shader or a program."};
    logErr(err, 1);
    return;
  }
  char* log = (char*)malloc(log_length);

  if (glIsShader(object))
    glGetShaderInfoLog(object, log_length, NULL, log);
  else if (glIsShader(object))
    glGetProgramInfoLog(object, log_length, NULL, log);

  //TODO: тут надо преобразовать тип "char" в тип "const char" для
  //переменной log (пока не знаю как, а компилятор не ругается)
  const char* log_msg[1] = { log };
  logErr(log_msg, 1);
  free(log);  
  return;
}

/* Создание и компиляция шейдерной программы*/
int init_resources(void)
{
  GLint compile_ok = GL_FALSE;
  GLint link_ok = GL_FALSE;

  int loaded = ogl_LoadFunctions();
  if (loaded == ogl_LOAD_FAILED)
  {
    int num_f = loaded - ogl_LOAD_SUCCEEDED;
    printf("Number of functions that failed to load: %i.\n", num_f);
    return 1;
  }

  // создание вершинного и фрагментного шэйдеров
  GLuint vs, fs;
  if ((vs = create_shader("triangle.v.glsl", GL_VERTEX_SHADER))   == 0)
    return 0;
  if ((fs = create_shader("triangle.f.glsl", GL_FRAGMENT_SHADER)) == 0)
    return 0;

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram:");
    return 0;
  }
  const char* attribute_name = "coord2d"; // имя атрибута для привязки к
                                          // программе вершинного шейдера -
                                          // координаты текущей вершины.
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if (-1 == attribute_coord2d) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return 0;
  }
  return 1;
}

/**
 * Компиляция шейдеров из файла с перехватом и отображением ошибок
 */
GLuint create_shader(const char* filename, GLenum type)
{
  const GLchar* source = file_read(filename);
  if (source == NULL)
  {
    const char* err[4] = {
      "Error open ",
      filename,
      ": ",
      SDL_GetError()
    };
    logErr(err, 4);
    return 0;
  }
  GLuint res = glCreateShader(type);
  const GLchar* sources[] = {
#ifdef GL_ES_VERSION_2_0
		"#version 100\n"  // OpenGL ES 2.0
#else
		"#version 120\n"  // OpenGL 2.1
#endif
	,
  source };
  glShaderSource(res, 2, sources, NULL);
  free((void*)source);

  glCompileShader(res);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
	  const char* msg[2] = {
      "Error compile ",
      filename
    };
    logErr(msg, 2);
    print_log(res);
		glDeleteShader(res);
		return 0;
	} 
	return res;
}

/* функция рисования изображения*/
void onDisplay(SDL_Window * window)
{
  glClear(GL_COLOR_BUFFER_BIT);

  // нарисовать треугольник используя шейдерную программу
  glUseProgram(program);
  glEnableVertexAttribArray(attribute_coord2d);
  GLfloat triangle_vertices[] = { 0.0,  0.8, -0.8, -0.8, 0.8, -0.8 };
  glVertexAttribPointer(
    attribute_coord2d, // атрибут
    2,                 // количество элементов на вершине, здесь две - (х, у).
    GL_FLOAT,          // тип каждого элемента
    GL_FALSE,          // принять наши параметры как есть
    0,                 // никаких дополнительных данных между каждой позицией
    triangle_vertices  // указатель на массив C.
    );
  /* Push each element in buffer_vertices to the vertex shader */
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(attribute_coord2d);
  SDL_GL_SwapWindow(window);
  return;
}

void free_resources(void)
{
  glDeleteProgram(program);
  return;
}

/** Цикл отображения окна приложения
 *  пока не появится событие SDL_QUIT
 */
void winDisp(SDL_Window * window)
{
  SDL_Event ev;
  SDL_PollEvent(&ev);
  while ( SDL_QUIT != ev.type ) {
   onDisplay(window);
    SDL_PollEvent(&ev);
  }
  return;
}

int main(int argc, char* argv[])
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(
    "My First SDL shaders",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    1024, 768,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(window);
  if (1 != init_resources()) return EXIT_FAILURE;
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.5, 0.69, 1.0, 1.0);

  winDisp(window);
  free_resources();
  return EXIT_SUCCESS;
}
