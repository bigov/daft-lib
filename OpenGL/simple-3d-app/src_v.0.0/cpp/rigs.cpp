#include "rigs.hpp"
#include <ctime>

namespace app {

/*
 * Журнал сообщений
 *
 * В текущей редакции пока только вывод информации в стандартный поток
 * или окно сообщений (если доступно).
 */
	void LogOutputFunction(void* userdata, int category,
				SDL_LogPriority priority, const char* message)
	{
		if (write_session_log(message)) return;
		std::cerr << message << std::endl;
		return;
	}

/**
 * A simple function that prints a message, the error code returned by SDL,
 * and quits the application
 */
void fail(const char *msg)
{
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "CRITICAL: %s", msg);
    SDL_Quit();
    exit(EXIT_FAILURE);
}

// silent check: the file is exist or not
bool file_exist(const char *file_pathname)
{
	bool rezult = false;
	SDL_RWops *rw = SDL_RWFromFile(file_pathname, "rb");
	if(rw != NULL)
	{
		rezult = true;
		SDL_RWclose(rw);
	}
	return rezult;
}

/**
 * Считывание даных из файла в память
 */
char* file_read(const char *pname)
{
	SDL_assert_paranoid(pname);
	Sint64 nb_read_total = 0, nb_read = 1;

	SDL_RWops* file = SDL_RWFromFile(pname, "rb");
	if (file == NULL) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
		return NULL;
	}
	Sint64 fsize = SDL_RWsize(file);
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

int write_session_log(const char* message)
{
	const char *fname = "trickrig.log";
	const char *nl = "\n";
	SDL_RWops *file = SDL_RWFromFile(fname, "a");
	if(file != NULL)
	{
		time_t ltime;
		struct tm *Tm;
		ltime=time(NULL);
		Tm=localtime(&ltime);
		char* timestamp = (char*)malloc(24);
		sprintf(timestamp, "%04d-%02d-%02d %02d:%02d:%02d  ", Tm->tm_year + 1900,
			Tm->tm_mon + 1,	Tm->tm_mday, Tm->tm_hour, Tm->tm_min, Tm->tm_sec);
		SDL_RWwrite(file, timestamp, 1, 21);
		free(timestamp);

		size_t len = SDL_strlen(message);
		if (SDL_RWwrite(file, message, 1, len) != len)
		{
			std::cerr << "Error on write file" << std::endl;
		}
		SDL_RWwrite(file, nl, 1, 1);
		SDL_RWclose(file);
	}
	return true;
}

} // namespace app
