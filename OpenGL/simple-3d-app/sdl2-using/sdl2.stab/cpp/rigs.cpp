#include "../hpp/rigs.hpp"

namespace app {

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

} // namespace app
