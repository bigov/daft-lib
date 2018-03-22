/*
 * file: config.cpp
 *
 * Инициализация, установка начальных значений, считывание/сохранение
 * кофигурации, настройка параметров.
 */

//#include <string>
#include <SDL2/SDL_syswm.h>
#include "rigs.hpp"

namespace app {

/*
 * Определение типа операционной системы, на которой запущено приложение,
 * при помощи создания скрытого тестового окна.
 */
	void Config::detect_os()
	{
		if(SDL_Init(SDL_INIT_VIDEO)) fail("Can't init SDL video subsystem");
		SDL_Window* w =
			SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
		if(NULL == w) fail(SDL_GetError());
    if(NULL == SDL_GL_CreateContext(w)) fail("Can't create context");
    gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
    if(NULL == didLoad) fail("Can't load OpenGL functions");

		// Get max supported versions of the OpenGl and GLSL
		gl::GetIntegerv(gl::MAJOR_VERSION, &major);
    gl::GetIntegerv(gl::MINOR_VERSION, &minor);
		glsl = gl::GetString(gl::SHADING_LANGUAGE_VERSION);

		SDL_SysWMinfo info;
		SDL_VERSION(&info.version); // init info structure (required)

		if(!SDL_GetWindowWMInfo(w, &info))
				SDL_Log("Can't determinate OS!");
		SDL_DestroyWindow(w);

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
		string *config_file = new string;
		*config_file = *run_dir + WORK_FNAME;

		if(!file_exist(config_file->c_str()))
			*config_file = *sys_dir + INI_FNAME;

		const char* ini = file_read(config_file->c_str());

		delete config_file;
		if(!ini) return;

		bool comment = false;
		bool value = false;
		string ini_key = "";
		string ini_val = "";
		while (*ini != '\0')
		{
			switch(*ini)
			{
				case '/':
					if (*(ini+1)=='/') comment = true;
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
		if(ini_cfg.count(key_name))
			return true;
		else
			SDL_Log("In the config not found key = %s", key_name);
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

	// save current params to the ini_cfg map
	void Config::flush_config()
	{
		ini_cfg["window_w"]   = std::to_string(*win0_w);
		ini_cfg["window_h"]   = std::to_string(*win0_h);
		ini_cfg["fullscreen"] = std::to_string(*win0_f);
		return;
	}

	// установка параметров
	void Config::get_ini_config()
	{
		SDL_LogResetPriorities();

		int key = iKey("debug");
		switch(key)
		{
			case 0:
				SDL_LogSetAllPriority(SDL_LOG_PRIORITY_CRITICAL);
				break;
			case 1:
				SDL_LogSetAllPriority(SDL_LOG_PRIORITY_ERROR);
				break;
			case 2:
				SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
				break;
			case 3:
				SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);
				break;
			case 4:
				SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
				break;
			case 5:
				SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
				break;
			default:
				SDL_LogSetAllPriority(SDL_LOG_PRIORITY_ERROR);
		}
		SDL_LogWarn(APP, "---------------- Start TrickRig --------------------");
		SDL_LogVerbose(APP, "Log level: %d/5", key);

		*win0_w = iKey("window_w");
		if (*win0_w == 0) *win0_w = 640;
		*win0_h = iKey("window_h");
		if (*win0_h == 0) *win0_h = 480;
		*win0_f = iKey("fullscreen");

		string* s = new string;

		*s = *sys_dir + sKey("images_dir") + ds + sKey("tex0");
		texture_pname = new char[s->length() + 1];
		std::strcpy(texture_pname, s->c_str());

		major = iKey("gl_version_major");
		minor = iKey("gl_version_minor");

		string *pglsl = new string;
		*pglsl = *sys_dir + sKey("shaders_dir") + ds + sKey("opengl_profile") +
			"_" + sKey("gl_version_major") + "." + sKey("gl_version_minor") + ds;

		*s = *pglsl + sKey("vert_shader");
		vshader_pname = new char[s->length() + 1];
		std::strcpy(vshader_pname, s->c_str());

		*s = *pglsl + sKey("frag_shader");
		fshader_pname = new char[s->length() + 1];
		std::strcpy(fshader_pname, s->c_str());

		delete s;
		delete pglsl;
		return;
	}

	// write current config params to the file WORK_FNAME
	void Config::save_config()
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

	Config::Config()
	{
		win0_w = new int;
		win0_h = new int;
		win0_f = new int;

		if (0 != SDL_Init(SDL_INIT_EVERYTHING))
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"",SDL_GetError(),NULL);

		if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) fail("Can't init SDL2_image.");

		SDL_LogSetOutputFunction(LogOutputFunction, NULL);

		detect_os();
		read_ini_file();
		get_ini_config();
		return;
	}

	Config::~Config()
	{
		save_config();
		delete win0_w;
		delete win0_h;
		delete win0_f;
		delete sys_dir;
		delete run_dir;
		//SDL_Quit();
		return;
	}

} // namespace app
