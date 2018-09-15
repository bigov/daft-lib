/*
 * file: config.cpp
 *
 * Инициализация, установка начальных значений, считывание/сохранение
 * кофигурации, настройка параметров.
 */

#include "config.hpp"

#ifndef SYS_DIR
#define SYS_DIR "sysdir"
#endif

#ifndef WORK_FNAME
#define WORK_FNAME "work.cfg"
#endif

#ifndef INI_FNAME
#define INI_FNAME "ini.cfg" // файл начальной настройки
#endif

using std::string;

#define _run std::runtime_error

namespace app {

	////
	//
	// Определение типа операционной системы, на которой запущено приложение,
	// при помощи создания скрытого тестового окна.
	//
	void Config::detect_os()
	{
		SDL_Window* w =
			SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);

		if(nullptr == w) throw _run("Fail create window on Config::detect_os");
    if(NULL == SDL_GL_CreateContext(w)) throw _run("Can't create context");
    gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
    if(NULL == didLoad) throw _run("Can't load OpenGL functions");

		// Get max supported versions of the OpenGl and GLSL
		gl::GetIntegerv(gl::MAJOR_VERSION, &major_ver);
    gl::GetIntegerv(gl::MINOR_VERSION, &minor_ver);

		SDL_SysWMinfo info;
		SDL_VERSION(&info.version); // init info structure (required)

		GLint rez = SDL_GetWindowWMInfo(w, &info);
		SDL_DestroyWindow(w);
		if(!rez) throw _run("Can't determinate OS!");
		
		// set Directory_Separator (ds)
		switch(info.subsystem)
		{
			case SDL_SYSWM_WINDOWS: ds = '\\'; break;
			default: ds = '/';
		}

		// set application data directory
		run_dir = new string(SDL_GetBasePath());
		sys_dir = new string(*run_dir + SYS_DIR + ds);

		return;
	}

	/** Считывание данных из файла настроек
		*
		* Заполнение вектора ini_cfg значениями полученных параметров.
		* В результате работы функции все указанные в кофигурационном файле
		* параметры в текстовом виде сохраняются в массиве ini_cfg.
		*/
	void Config::read_ini_file()
	{
		string * config_file = new string(*run_dir + WORK_FNAME);

		if(!lib::sdl_file_exist(config_file->c_str()))
			*config_file = *sys_dir + INI_FNAME;

		const char* ini = lib::sdl_file_read(config_file->c_str());
		delete config_file;
		if(!ini) throw _run("can't read " + *config_file);

		bool comment = false;
		bool value = false;
		string ini_key = "";
		string ini_val = "";
		while (*ini != '\0')
		{
			switch(*ini)
			{
				case '/':
					if (*(ini+1)=='/')
						{ comment = true; }
					else
						{ if((!comment) && value) ini_val += *ini; }
					break;
				case '\r': case '\n':
					comment = false;
					if( value && (ini_key.size() > 0))
						ini_cfg[ini_key]=ini_val;
					value = false;
					ini_key = "";
					ini_val = "";
					break;
				case ' ': case '\t':
					break;
				case '=':
					if(!comment) value = true;
					break;
				default:
					if(!comment)
					{
						if(!value)
						{
							ini_key += *ini;
						} else
						{
							ini_val += *ini;
						}
					}
					break;
			}
			ini++;
		}
		return;
	}

	// Check if the key_name is present in the config file (map ini_cfg)
	int Config::ini_key_is_present(const char* key_name)
	{
		if(ini_cfg.count(key_name)) return true;
		SDL_Log("In the config not found the key = %s", key_name);
		return false;
	}

	// Get key from the map ini_cfg
	int Config::iKey(const char* key_name)
	{
		if(ini_key_is_present(key_name))
		{
			return atoi(ini_cfg[key_name].c_str());
		}	else
		{
			return 0;
		}
	}

	// TODO: remove?
	// Get char key from the map ini_cfg
	char Config::cKey(const char* key_name)
	{
		if(ini_key_is_present(key_name))
		{
			return ini_cfg[key_name][0];
		}	else {
			return '\0';
		}
	}

	// Get key from the map ini_cfg
	string Config::sKey(const char* key_name)
	{
		if(ini_key_is_present(key_name))
		{
			return ini_cfg[key_name];
		}	else
		{
			return "";
		}
	}

	// Copy current params to the ini_cfg map
	void Config::flush_config()
	{
		ini_cfg["window_w"]   = std::to_string(gui.W);
		ini_cfg["window_h"]   = std::to_string(gui.H);
		ini_cfg["fullscreen"] = std::to_string(gui.F);
		return;
	}

	// установка параметров
	void Config::get_ini_config()
	{
		
		std::string s = sKey("log_fname");
		if(!s.empty())
		{
			size_t pos = s.find(ds);
    	if (pos == std::string::npos)
				{	lib::set_log_fname(*run_dir + s); }
			else
				{ lib::set_log_fname(s); }
		}
		
		gui.W = iKey("window_w");
		if (gui.W == 0) gui.W = 640;
		gui.H = iKey("window_h");
		if (gui.H == 0) gui.H = 480;
		gui.F = iKey("fullscreen");

		content.texture_pname = new string(*sys_dir + sKey("images_dir")
			+ ds + sKey("tex0"));

		gui.major = iKey("gl_version_major");
		gui.minor = iKey("gl_version_minor");
	
		content.vshader_pname = new string(*sys_dir + sKey("shaders_dir")
			+ ds + sKey("vert_shader"));
		
		content.fshader_pname = new string(*sys_dir + sKey("shaders_dir") 
			+ ds + sKey("frag_shader"));

		return;
	}

	// write current config params to the file WORK_FNAME
	void Config::save()
	{
		flush_config();

		string config;
		for ( std::map<string,string>::iterator it = ini_cfg.begin();
				it !=ini_cfg.end() ; ++it )
		{
			config += it->first + " = " + it->second + "\n";
		}

		string *fname = new string(*run_dir + WORK_FNAME);
		SDL_RWops *rw = SDL_RWFromFile(fname->c_str(), "w");
		delete fname;

		if(rw != NULL)
		{
			size_t len = SDL_strlen(config.c_str());
			if (SDL_RWwrite(rw, config.c_str(), 1, len) != len)
			{
				SDL_LogDebug(APP, "Err saving config");
			}
			SDL_RWclose(rw);
		}
		return;
	}

	Config::Config(int argc, char * argv[]) :
		ini_cfg(), run_dir(nullptr), sys_dir(nullptr), ds(), major_ver(3),
		minor_ver(0), server(), gui(), content() 
	{
		if(argc) if(argv) argc = 0; //затычка для статического анализатора
		
		detect_os();
		read_ini_file();
		get_ini_config();

		return;
	}

	Config::~Config()
	{
		delete sys_dir;
		delete run_dir;
		delete content.texture_pname;
		delete content.vshader_pname;
		delete content.fshader_pname;
		//SDL_Quit();
		return;
	}

} // namespace app
