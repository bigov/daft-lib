//
// file io.cpp
//
// функции чтения/записи файлов и вывода сообщений
//

#include "lib.hpp"

#ifndef RELEASE
#define RELEASE 0
#endif

namespace lib {

// silent check: the file is exist or not
bool sdl_file_exist(const char* file_pathname)
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
 *
 * !!! Необходимо освобождать память из под char
 */
char* sdl_file_read(const char* pname)
{
	if(!sdl_file_exist(pname))
	{ 
		show_error(SDL_GetError());
		return nullptr;
	}

	size_t 
		nb_read_total = 0,
		nb_read = 1,
		fsize;

	SDL_RWops* file = SDL_RWFromFile(pname, "rb");
	if (file == NULL) {
		show_error(SDL_GetError());
		return nullptr;
	}
	Sint64 safe_fsize = SDL_RWsize(file);
	if(safe_fsize < 1) return nullptr;

	fsize = (size_t)safe_fsize;

	char* content = new char[fsize + 1];
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


////
//	 "Черный список" имен файлов
//   (Защита от повторной проверки одного и того-же имени файла)
//
// - set = 0        ( запрос присутствия имени в черном списке)
// - set = 1        ( имя вносится в черный список            )
// - set != 1 || 0  ( имя удаляется из черного списка         )
//
bool bl_fname_set(const std::string &, int);

// запрос присутствия имени в черном списке
bool bl_fname(const std::string & f) { return bl_fname_set(f, 0); }

// установка черного списка (внеcение/удаление)
bool bl_fname_set(const std::string & filepath, int set)
{
	static std::list<std::string> blacklist;
	std::list<std::string>::iterator bi;
	switch (set)
	{
		case 0:
			bi = std::find(blacklist.begin(), blacklist.end(), filepath);
			return (bi != blacklist.end());
		case 1:
			if(!bl_fname(filepath))
			{
				blacklist.push_back(filepath);
				show_error((std::string)std::strerror(errno) + 
					"\n\ncan't open file:\n" + filepath + "\n");
			}
			return true;
		default:
			if(bl_fname(filepath)) blacklist.remove(filepath);
			return false;
	}
}

////
// 	Проверка доступа и корректности имени файла
//
bool filepath_ok(const std::string & filepath)
{
	char * ptrfname = new char[filepath.length() + 1];
	ptrfname[filepath.copy(ptrfname, std::string::npos)] = '\0';
	int fd = open(ptrfname, O_CREAT, S_IRUSR | S_IWUSR);
	delete ptrfname;

	if(0 > fd) { 
		if(!bl_fname(filepath)) bl_fname_set(filepath, 1);
		return false;
	} else { 
		close(fd);
		if(bl_fname(filepath)) bl_fname_set(filepath, -1);
		return true;
	}
}

////
// Последнее средство, если ничего больше не удалось - стандартный вывод:
// 
void msg_out_console(const std::string & msg)
{
	//std::cerr << "trickrig err: " << msg.c_str() << std::endl;
	std::cout << msg.c_str() << std::endl;
	return;
}

////
// запись информации об ошибке в файл в текущем каталоге,
// в случае неудачи - в стандартный вывод
//
void out_debug_file(const std::string & msg)
{
	if(msg.empty()) return;
	const char * fname = "DEBUG.TXT";

	int fd = open(fname,
		O_CREAT | O_WRONLY | O_APPEND,
		S_IRUSR | S_IWUSR  | S_IRGRP | S_IROTH
	);

	if(fd > 0)
	{
		long unsigned int count = msg.length() + 1;
		char * m = new char[count]; // создать буфер для вывода текста
		m[msg.copy(m, std::string::npos)] = '\n'; // скопировать текст в буфер
		m[count] = '\0';
		long int w = write(fd, m, count); // передать данные в файл
		if(w < 1)
		{
			msg_out_console(msg);
		} else
		{
			if((long unsigned int)w != count)
				msg_out_console("message was truncated");
		}

#ifndef __MS_WIN__
// в версии mingw-w64 эта функция отсутствует
		fsync(fd); // сбросить кэш
#endif

close(fd); // закрыть файл
		delete [] m; // освободить память из под буфера
	} else {
		msg_out_console(msg); // если файл не открылся, то вывести на консоль
	}
	return;
}

////
// Запись в файл журнала
//
void _write_log(const std::string & message, const std::string & log_file_name)
{
	static std::string fname;

	if(!log_file_name.empty() && filepath_ok(log_file_name))
		fname = log_file_name;
	if(fname.empty()) fname = "logfile.txt";
	if(message.empty()) return;

	SDL_RWops * file = SDL_RWFromFile(fname.c_str(), "a");
	if(NULL != file)
	{
		time_t ltime;
		struct tm * Tm;
		ltime = time(NULL);
		Tm = localtime(&ltime);
		
		char * timestamp = (char*)malloc(24);
		sprintf(timestamp, "%04d-%02d-%02d %02d:%02d:%02d  ", Tm->tm_year + 1900,
			Tm->tm_mon + 1,	Tm->tm_mday, Tm->tm_hour, Tm->tm_min, Tm->tm_sec);
		SDL_RWwrite(file, timestamp, 1, 21);
		free(timestamp);

		size_t len = message.size();
		if (SDL_RWwrite(file, message.c_str(), 1, len) != len) 
		{
			out_debug_file(" Error writing in the file: " + fname +
									 "\n Message: " + message);
		}
		SDL_RWwrite(file, "\n", 1, 1);
		SDL_RWclose(file);
	} else {
		out_debug_file("Can't write logfile: " + fname + "\n");
		out_debug_file(SDL_GetError());
		out_debug_file(message);
	}
	return;
}

void write_log(const std::string & message)
{ 
	_write_log(message, "");
	return;
}

////
// Установка имени файла журнала
//
void set_log_fname(const std::string & log_file_name)
{
	_write_log("", log_file_name);
	return;
}

////
// Всплывающее окно с информацией
//
// в случае неудачи вывода окна текст сообщения записывается в файл
//
void show_message(const std::string & message)
{
	// For release do disable PopUps
	if(RELEASE == 1)
	{
		write_log(message);
		return;
	}
	
	if(0 > SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"TrickRig",	message.c_str(), NULL))
	{
		write_log(message);
	}

	return;
}

////
// Show resived message and (if exist) error message from SDL_GetError
//
void show_error(const std::string & m)
{
	std::string msg = m;
	if (strlen(SDL_GetError()) > 1)
	{
		msg += ":\n" + (std::string)SDL_GetError();
		SDL_ClearError();
	}
	show_message(msg);
	return;
}

} // namespace lib
