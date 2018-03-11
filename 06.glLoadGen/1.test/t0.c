/**
 *
 */

#include <stdio.h>
#include "gl_core_2_1.h"
#include <SDL2/SDL.h>

GLuint program;
GLint attribute_coord2d;

/* —оздание и компил€ци€ шейдерной программы*/
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

  // создание вершинного шэйдера
  const char *vs_source =
    "#version 120\n                           "
    "attribute vec2 coord2d;                  "
    "void main(void) {                        "
    "  gl_Position = vec4(coord2d, 0.0, 1.0); "
    "}                                        ";

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vs_source, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
  if (0 == compile_ok) {
    printf("Error in vertex shader\n");
    return 0;
  }

  /** —оздание фрагментного шейдера
   *
   *  «десь минимальными средствами создаетс€ шейдер с плавным
   *  изменением цвета пиксел€ в зависимости от его координат
   *  и чередованием полос прозрачности (gl_FragColor[3])
   */
  const char *fs_source =
    "#version 120\n                           "
    "void main(void) {                        "
    "gl_FragColor[0] = gl_FragCoord.x/640.0;  "
    "gl_FragColor[1] = gl_FragCoord.y/480.0;  "
    "gl_FragColor[2] = 0.5;                   "
    "  if (mod(gl_FragCoord.y, 30.0) > 15)    "
    "gl_FragColor[3] = 1;                     "
    "  else                                   "
    "gl_FragColor[3] = 0.4;                   "
    "}                                        ";

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fs_source, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
  if (!compile_ok) {
    printf("Error in fragment shader\n");
    return 0;
  }

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    printf("glLinkProgram:");
    return 0;
  }
  const char* attribute_name = "coord2d"; // им€ атрибута дл€ прив€зки к
                                          // программе вершинного шейдера -
                                          // координаты текущей вершины.
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if (-1 == attribute_coord2d) {
    printf("Could not bind attribute %s\n", attribute_name);
    return 0;
  }
  return 1;
}

/* функци€ рисовани€ изображени€*/
void onDisplay(SDL_Window * window)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.85, 0.85, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // нарисовать треугольник использу€ шейдерную программу
  glUseProgram(program);
  glEnableVertexAttribArray(attribute_coord2d);
  GLfloat triangle_vertices[] = { 0.0,  0.8, -0.8, -0.8, 0.8, -0.8 };
  glVertexAttribPointer(
    attribute_coord2d, // атрибут
    2,                 // количество элементов на вершине, здесь две - (х, у).
    GL_FLOAT,          // тип каждого элемента
    GL_FALSE,          // прин€ть наши параметры как есть
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

/** ÷икл отображени€ окна приложени€
 *  пока не по€витс€ событие SDL_QUIT
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
  //printf("\ndebug exit\n");
  //return 0;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(
    "SDL shaders",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    1024, 768,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(window);

  if (1 != init_resources()) return EXIT_FAILURE;

  winDisp(window);
  free_resources();
  return EXIT_SUCCESS;

}


