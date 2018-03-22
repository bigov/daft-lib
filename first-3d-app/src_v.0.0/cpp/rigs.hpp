#ifndef _RIGS_
#define _RIGS_

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gl_com_4_5.hpp"

#define SYS_DIR "sysdir"
#define INI_FNAME "ini.cfg"   // файл начальной настройки
#define WORK_FNAME "work.cfg" // файл текущих настроек (создается после
															// закрытия приложения)
#define APP SDL_LOG_CATEGORY_APPLICATION

using std::string;
using std::cerr;
using std::endl;
using std::cout;

namespace app {

	typedef char* PathName;

	struct Rods {
		bool forward  = false;
		bool backward = false;
		bool left     = false;
		bool right    = false;
		bool up       = false;
		bool down     = false;
		bool fast     = false;
		bool slow     = false;
		bool fly      = false;
		bool climb    = false;
		bool creep    = false;
	};

	// text.cpp
	extern void show_text(const char *message, int screen_w, int screen_h);

	// rigs.cpp
	extern void LogOutputFunction(void* userdata, int category,
			SDL_LogPriority priority, const char* message);
	extern void fail(const char* fail_message);
	extern bool file_exist(const char* file_pathname);
	extern char* file_read(const char* file_pathname);
	extern int write_session_log(const char* message);

	// config.cpp
	class Config
	{
		void detect_os(void);        // определение операционной системы
		void read_ini_file(void);	       // чтение настроек из файла ini
		void get_ini_config(void);   // установка параметров
		void flush_config(void);
		void save_config(void);		   // сохранение настроек
		int ini_key_is_present(const char* key_name);
		int iKey(const char* key_name);
		char cKey(const char* key_name);
		string sKey(const char* key_name);

		std::map <string, string> ini_cfg;

		public:

			string *run_dir;	// application directory running from
			string *sys_dir;	// data directory
			char ds;					// directory separatora
			GLint major;				// OpenGL version using
			GLint minor;

			// main window width, height, x, y, fullscreen mode
			int *win0_w;
			int *win0_h;
			int *win0_f;

			const GLubyte *glsl;		// version GLSL

			char *vshader_pname; // имя файла векторного шейдера
			char *fshader_pname; // -- фрагментного --
			char *texture_pname; // имя файла с текстурой

			Config(void);
			~Config(void);
	};

	class Shader
	{
		GLuint uid;
    int *ref;

    void store(void);
    void release(void);
		void init(const GLchar *source, GLenum shaderType);
		bool ready(void);
		void check_errors(void);
		void set_tname(GLenum shaderType);
		char* tname;

		public:

			Shader(const PathName file, GLenum shaderType);
			Shader(const GLchar *source, GLenum shaderType);
      ~Shader(void);

      Shader(const Shader& other);
      Shader& operator=(const Shader& other);

      GLuint id(void) const;
	};

	class Prog
	{
		// uint for build objects, returned from gl::CreateProgram
		GLint uid;
		// ban copying
		Prog(const Prog& other);
		const Prog& operator=(const Prog& other);

		bool ready(void);
		void check_errors(void);

		public:
			Prog();
			Prog(const std::vector<Shader>& shaders_array);
			~Prog();

			GLint id() const;
			//using gl::GetAttribLocation
			GLint attrib(const GLchar *attribName) const;
			//using gl::GetUniformLocation
      GLint uniform(const GLchar *uniformName) const;

      void use() const;
      bool isInUse() const;
      void stopUsing() const;
	};

	// content.cpp
	extern void set_vertices(GLuint *vbo_vertices);
	extern void bind_elements(GLuint *ibo_elements);
	extern void set_texcoords(GLuint *vbo_texcoords);
	extern bool bind_texture(GLuint *id, const char *filename);
	extern void content_create(Config *config_params);
	extern void render_content(float window_aspect, Rods motion_type);
	extern void free_resources();

} // namespace app

#endif
