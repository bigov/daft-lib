#include <stdio.h>
#include "gl_core_3_3.h"
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>

void print_opengl_version(void)
{

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(" ", 0, 0, 1, 1,
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(window);

  int loaded = ogl_LoadFunctions();
  if (loaded == ogl_LOAD_FAILED) {
    int num_f = loaded - ogl_LOAD_SUCCEEDED;
    printf("Number of functions that failed to load: %i.\n", num_f);
    return;
  }

  const GLubyte *renderer = glGetString( GL_RENDERER );
  const GLubyte *vendor   = glGetString( GL_VENDOR   );
  const GLubyte *version  = glGetString( GL_VERSION  );
  const GLubyte *glslVer  = glGetString( GL_SHADING_LANGUAGE_VERSION );

  GLint major, minor;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  glGetIntegerv(GL_MINOR_VERSION, &minor);

  printf("\nRenderer: %s\n", renderer);
  printf("Vendor: %s\n", vendor  );
  printf("OpenGL version: %d.%d\n", major, minor );
  printf("OpenGL driver: %s\n", version );
  printf("GLSL Version: %s\n", glslVer );
  return;
}

int main(int argc, char *argv[])
{
  print_opengl_version();
  return 0;
}
