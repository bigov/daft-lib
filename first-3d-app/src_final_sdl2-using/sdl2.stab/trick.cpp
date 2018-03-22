/**
 * file: appmain.cpp
 *
 * Startup application
 *
 */

#ifndef SDL_ASSERT_LEVEL
	#define SDL_ASSERT_LEVEL 3
#endif

#include "hpp/main.hpp"

////
// Перенаправление для функции SDL_Log
//
void LogOutputFunction(void * d, int c, SDL_LogPriority p, const char * ms)
{
	if(d) if(c) if(p) c = 0; // заглушка для статического анализатора
	std::string message(ms, sizeof(ms)); 
	write_log(message);
	return;
}

////
// Инициализация библиотеки SDL2
//
void init_lib_sdl() throw(app::Flaw)
{
	if(SDL_Init(SDL_INIT_EVERYTHING)) throw app::Flaw("Can't init SDL-lib.");
	SDL_LogSetOutputFunction(LogOutputFunction, NULL);
	if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
			 throw app::Flaw("Can't init SDL2_image lib");
	return;
}

int main(int argc, char * argv[])
{
	try
	{
		init_lib_sdl();

		app::Config config(argc, argv);
		app::Server server = app::Server(&config.server);
		app::GUI gui = app::GUI(&config.gui);

		server.start();
		gui.show(&config.content);

		// завершение работы приложения
		server.stop();
		config.save();
	}	
	catch(app::Flaw & e)
	{
		show_error(e.what());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Quit();
	return EXIT_SUCCESS;
}
