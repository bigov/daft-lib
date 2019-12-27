#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *win = NULL;
	win = SDL_CreateWindow("",0,0,0,0,SDL_WINDOW_HIDDEN |	SDL_WINDOW_OPENGL);
	if(NULL == win) std::cerr << "ABORT: Can't create SDL window.\n";
	SDL_GL_CreateContext(win);

  GLint major = 0;
	GLint minor = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *glslVer  = glGetString(GL_SHADING_LANGUAGE_VERSION);
	SDL_DestroyWindow(win);

	char msg [128];
	sprintf( msg, "\nVideo: %s\n", renderer);
	renderer = NULL;

	char ver [32];
	sprintf(ver, "OpenGL version: %i.%i\n", major, minor);
	strcat(msg, ver);

	char glsl [32];
	sprintf(glsl, "GLSL version: %s", glslVer);
	strcat(msg, glsl);
	glslVer = NULL;

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
			"Test OpenGL", msg, NULL);

	SDL_Quit();
	return 0;
}

