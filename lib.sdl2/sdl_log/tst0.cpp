#include <SDL2/SDL.h>
#include <iostream>
#include <cassert>
/**
 * SDL_Log
 * message with SDL_LOG_CATEGORY_APPLICATION and SDL_LOG_PRIORITY_INFO
 *
	category
		SDL_LOG_CATEGORY_APPLICATION
		SDL_LOG_CATEGORY_ERROR
		SDL_LOG_CATEGORY_SYSTEM
		SDL_LOG_CATEGORY_AUDIO
		SDL_LOG_CATEGORY_VIDEO
		SDL_LOG_CATEGORY_RENDER
		SDL_LOG_CATEGORY_INPUT
		SDL_LOG_CATEGORY_RESERVED0..9
		SDL_LOG_CATEGORY_CUSTOM

	priority
		SDL_LOG_PRIORITY_VERBOSE
		SDL_LOG_PRIORITY_DEBUG
		SDL_LOG_PRIORITY_INFO
		SDL_LOG_PRIORITY_WARN
		SDL_LOG_PRIORITY_ERROR
		SDL_LOG_PRIORITY_CRITICAL
		SDL_NUM_LOG_PRIORITIES
 */

namespace my {

	int pop(const char* message)
	{
		std::string *s_text = new std::string(message);
		*s_text = "\n      " + *s_text + "      \n";

		const SDL_MessageBoxButtonData buttons[] =
		{
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, " OK " },
		};

		const SDL_MessageBoxColorScheme colorScheme =
		{
			{ /* .colors (.r, .g, .b) */
				/* [SDL_MESSAGEBOX_COLOR_BACKGROUND]         */
				{ 200, 200, 200 },
				/* [SDL_MESSAGEBOX_COLOR_TEXT]               */
				{  33,  33,  33 },
				/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]      */
				{ 111, 181, 255 },
				/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]	 */
				{  78, 139, 203 },
				/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]	    */
				{  156,  33,  33 }
			}
		};
		//SDL_SetWindowMinimumSize(NULL, 600, 400);

		const char* title = "IMPORTANT!";
		const SDL_MessageBoxData messageboxdata =
		{
			SDL_MESSAGEBOX_WARNING, /* .flags */
			NULL, /* .window */
			title,
			s_text->c_str(),
			SDL_arraysize(buttons), /* .numbuttons */
			buttons, /* .buttons */
			&colorScheme /* .colorScheme */
		};
	int buttonid;
	int rez = SDL_ShowMessageBox(&messageboxdata, &buttonid);
	delete s_text;

	if (rez	< 0) return -2;
	return buttonid;
	}

	void app_logger(void *userdata,	int	category,
				SDL_LogPriority priority,	const char *message)
	{
		std::cout << message << std::endl;
		pop(message);
		return;
	}

	void check_messages(void) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "\t\tcritical");
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "\t\terror");
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "\t\twarn");
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "\t\tinfo");
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "\t\tdebug");
		SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "\t\tverbose");

		return;
	}

	bool video_on(void)
	{
		if(0 != SDL_VideoInit(NULL))
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
		SDL_assert(SDL_GetNumVideoDrivers() > 0);
		return true;
  }

	bool sdl_on(void)
	{
		if(0 != SDL_Init(0))
		{
			std::cerr << SDL_GetError() << std::endl;
			return false;
		}
		return video_on();
	}

	int tests(void)
	{

		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
				"\ndefault = %i  ---------------\n", 0);
		check_messages();

		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
				"\nverbose = %i  ---------------\n", SDL_LOG_PRIORITY_VERBOSE);
		check_messages();

		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
				"\ndebug = %i    ---------------\n", SDL_LOG_PRIORITY_DEBUG);
		check_messages();

		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
				"\ninfo = %i     ---------------\n", SDL_LOG_PRIORITY_INFO);
		check_messages();

		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
				"\nwarn = %i     ---------------\n", SDL_LOG_PRIORITY_WARN);
		check_messages();

		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_ERROR);
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
				"\nerror = %i    ---------------\n", SDL_LOG_PRIORITY_ERROR);
		check_messages();

		SDL_LogSetAllPriority(SDL_LOG_PRIORITY_CRITICAL);
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
				"\ncritical = %i ---------------\n", SDL_LOG_PRIORITY_CRITICAL);
		check_messages();

		return 0;
	}


} //namespace my

int main(int argc, char* argv[])
{
	my::sdl_on();
	SDL_LogSetOutputFunction(my::app_logger, NULL);

	int res = 0;
	res = my::tests();
	return res;
}
