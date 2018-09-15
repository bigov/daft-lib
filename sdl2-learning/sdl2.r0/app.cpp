//============================================================================
//
// file: appmain.cpp
//
// Main file - start application.
//
//============================================================================
#include "gui.hpp"

////////
// Инициализация библиотеки SDL2
//
void init_lib_sdl()
{
	if(SDL_Init(SDL_INIT_EVERYTHING))
		throw std::runtime_error("Can't init SDL-lib.");
	if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
		throw std::runtime_error("Can't init SDL2_image lib");
	return;
}

////////
// Вход
//
int main(int argc, char * argv[])
{
	try
	{
		init_lib_sdl();
		app::Config config(argc, argv);
		// TODO: два раза передается конфиг - надо сделать один.
		app::GUI gui(&config.gui);
		gui.show(&config.content);
		config.save();
		SDL_Quit();
		return EXIT_SUCCESS;
	}	
	catch(std::exception & e)
	{
		lib::show_error(e.what());
	}
	return EXIT_FAILURE;
}
