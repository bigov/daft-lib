// Example program:
// Using SDL2 to create an application window

#include "SDL2/SDL.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

  SDL_Window *window;                    // Declare a pointer
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
    "An SDL2 window",                  // window title
    SDL_WINDOWPOS_UNDEFINED,           // initial x position
    SDL_WINDOWPOS_UNDEFINED,           // initial y position
    800,                               // width, in pixels
    600,                               // height, in pixels
    SDL_WINDOW_OPENGL                  // flags - see below
  );
  SDL_GL_CreateContext(window);

  // Check that the window was successfully created
  if (window == NULL) {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  int stop = 0;
  while ( 1 != stop) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
		  if (event.type == SDL_QUIT)
			stop = 1;
		}
  }

  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
