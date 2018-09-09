/**
 * file: appmain.cpp
 *
 * Startup application
 *
 */

/* level of assertions: SDL_assert_paranoid, SDL_assert_release, SDL_assert
 Setup level:	3(all), 2(assert+assert_release), 1(assert_release), 0(off) */
#define SDL_ASSERT_LEVEL 2

#include "cpp/gui.hpp"

int main(int argc, char* argv[])
{
	app::GUI *gui = new app::GUI();
	gui->show();
	delete gui;
	return EXIT_SUCCESS;
}
