////
//
// file: config.hpp
//
// Header of class Config
//

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

// небольшой "хук" для сокращения размера текста в коде вызова SDL_Log
#define APP SDL_LOG_CATEGORY_APPLICATION

#include "flaw.hpp"

namespace app {

	struct Conf_Server
	{
		int state;
	};

	struct Conf_GUI
	{
		int F; // fullscreen mode
		int X; // position X
		int Y; // position Y
		int W; // width
		int H; // height
		int major; // version OpenGL setup for current use
		int minor; // subversion OpenGL setup for current use
	};

		struct Conf_Content
	{
		std::string * vshader_pname; // имя файла векторного шейдера
		std::string * fshader_pname; // -- фрагментного --
		std::string * texture_pname; // имя файла с текстурой
	};

	// config.cpp
	class Config
	{
		private:
			std::map <std::string, std::string> ini_cfg;

			operator=(const Config & );
			Config(const Config &);
			void detect_os(void) throw(errCfg); // определение операционной системы
			void read_ini_file(void) throw(errCfg); // чтение настроек из файла ini
			void get_ini_config(void) throw(errCfg); // установка параметров
			void flush_config(void);
			void save_config(void); // сохранение настроек
			int ini_key_is_present(const char * key_name);
			int iKey(const char * key_name);
			char cKey(const char * key_name);
			std::string sKey(const char * key_name);
		
		public:
			std::string * run_dir;	// application directory running from
			std::string * sys_dir;	// data directory
			char ds; // directory separator
			GLint major; // OpenGL version max supported
			GLint minor; // --||--
			Conf_Server server;
			Conf_GUI gui;
			Conf_Content content;

			Config(int argc, char * argv[]) throw(errCfg);
			~Config();
			void save(void);
	};
} // namespace app

#endif
