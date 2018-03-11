/**
 *
 * Creating program from shders array
 *
 */
#include "rigs.hpp"

namespace app
{
	Shader::Shader(const PathName file, GLenum type): uid(0), ref(NULL)
	{
		const GLchar *source = file_read(file);
		if(!source)
		{
			SDL_Log("Error load shader from file:\n\n%s", file);
			return;
		}
		init(source, type);
		free((GLchar*)source);
		// Необходимо для указания имени файла, в котором произошла ошибка
		if(0 == uid) SDL_Log("Error load shader from %s", file);
	}

	// После вызова конструктора в вызывающей функции следует освободить
	// блок памяти, в который помещен исходный код для компиляции шейдера. По
	// принципу "Выделение и освобождение памяти в одной функции".
	//
	Shader::Shader(const GLchar *source, GLenum type): uid(0), ref(NULL)
	{
		init(source, type);
	}

	Shader::Shader(const Shader& other) :
		uid(other.uid), ref(other.ref), tname(other.tname)
	{
		store();
	}

	Shader& Shader::operator = (const Shader& other)
	{
		release();
		uid = other.uid;
		ref = other.ref;
		tname = other.tname;
		store();
		SDL_LogVerbose(APP, "%s %d.%d copy as %d.%d",
				tname, uid, *(other.ref), uid, *ref);
		return *this;
	}

	/* Преобразование кода типа шэйдера в название типа (для отладки) */
	void Shader::set_tname(GLenum shaderType)
	{
		tname = (char*)malloc(9);

		if(shaderType == gl::VERTEX_SHADER)
			sprintf(tname, "V.shader");
		else if(shaderType == gl::FRAGMENT_SHADER)
			sprintf(tname, "F.shader");
		else
			sprintf(tname, "0.shader");

		return;
	}

	void Shader::init(const GLchar *source, GLenum shaderType)
	{
		set_tname(shaderType);

		uid = gl::CreateShader(shaderType);
		if(1 > uid)	{
			SDL_LogError(APP, "Creating shader error: %s", SDL_GetError());
			return;
		} else {
			SDL_LogVerbose(APP,	"%s %d created", tname, uid);
		}

		GLchar const *sources[] = { source, };
		GLint len[] = { (GLint)strlen(source), };

		gl::ShaderSource(uid, 1, sources, len);
		gl::CompileShader(uid);

		if(ready()) ref = new int(1);

		return;
	}

	GLuint Shader::id() const
	{
		return uid;
	}

	void Shader::check_errors()
	{
		GLint log_lenght = 0;
		if (gl::IsShader(uid))
		{
			gl::GetShaderiv(uid, gl::INFO_LOG_LENGTH, &log_lenght);
		} else {
			SDL_Log("The shader compiling was fail.");
			return;
		}

		// if log is empty
		if(2 > log_lenght) return;

		char *msg = (char*)malloc(log_lenght);
		gl::GetShaderInfoLog(uid, log_lenght, NULL, msg);
		SDL_LogDebug(APP, msg);
		free(msg);
		return;
	}

	// check errors
	bool Shader::ready()
	{
		GLint ok;
		gl::GetShaderiv(uid, gl::COMPILE_STATUS, &ok);
		check_errors(); // check compiling shader warnings
		if (!ok)
		{
			gl::DeleteShader(uid);
			SDL_LogError(APP,	"Err Shader %s", SDL_GetError());
			uid = 0;
			return false;
		}
		return true;
	}

	void Shader::store()
	{
		if (NULL == ref) {
			SDL_LogError(APP,	"Err: try to copy NULL shader");
			return;
		}
		*ref += 1;
		//SDL_LogVerbose(APP,	"%s %d.%d link", tname, uid, *ref);
		return;
	}

	Shader::~Shader()
	{
		if(NULL != ref)
			release();
		else
			SDL_LogError(APP, "Can't release NULL shader");
		return;
	}

	void Shader::release()
	{
		if(*ref > 0)
		{
			//SDL_LogVerbose(APP, "%s %d.%d remove", tname, uid, *ref);
			*ref -= 1;
		}

		if(*ref == 0)
		{
			SDL_LogVerbose(APP, "%s %d destroy", tname, uid);
			free((char*)tname);
			gl::DeleteShader(uid);
			uid = 0;
			delete ref;
		}
		return;
	}
	// ======================== programm class =============================

	Prog::Prog(const std::vector<Shader>& shaders_array) : uid(0)
	{
		if(shaders_array.size() < 1)
		{
			SDL_LogError(APP, "Err: empty shaders array");
			return;
		}

		uid = gl::CreateProgram();
		if(0 == uid)
		{
			SDL_LogError(APP, "Err create program: %s", SDL_GetError());
			return;
		}

		for(unsigned i = 0; i < shaders_array.size(); ++i)
			gl::AttachShader(uid, shaders_array[i].id());
		gl::LinkProgram(uid);
		for(unsigned i = 0; i < shaders_array.size(); ++i)
			gl::DetachShader(uid, shaders_array[i].id());

		if(!ready())
		{
			SDL_LogError(APP, "Err ready program: %s", SDL_GetError());
			gl::DeleteProgram(uid);
			uid = 0;
			return;
		}
		SDL_LogVerbose(APP, "Program %d created", uid);
		return;
	}

	// Will display errors if debug level > 2
	void Prog::check_errors()
	{
		SDL_assert(gl::IsProgram(uid));
		GLint log_lenght = 0;
		gl::GetProgramiv(uid, gl::INFO_LOG_LENGTH, &log_lenght);
		if(2 > log_lenght) return;
		char *log_info = (char*)malloc(log_lenght);
		gl::GetProgramInfoLog(uid, log_lenght, NULL, log_info);
		SDL_Log(log_info);
		free(log_info);
		return;
	}

	bool Prog::ready()
	{
		check_errors();
		GLint link_ok;
		gl::GetProgramiv(uid, gl::LINK_STATUS, &link_ok);
		return link_ok;
	}

	Prog::~Prog()
	{
		if(0 != uid)
		{
			stopUsing();
			gl::DeleteProgram(uid);
			SDL_LogVerbose(APP, "Program %i deleted.", uid);
			uid = 0;
		}
		return;
	}

	GLint Prog::id() const
	{
		return uid;
	}

	GLint Prog::attrib(const GLchar *attribName) const
	{
		SDL_assert(attribName && *attribName);
		GLint attrib = gl::GetAttribLocation(uid, attribName);
    SDL_assert(-1 != attrib);
		return attrib;
	}

  GLint Prog::uniform(const GLchar *uniformName) const
	{
		SDL_assert(uniformName && *uniformName);
    GLint uniform = gl::GetUniformLocation(uid, uniformName);
    SDL_assert(-1 != uniform);
		return uniform;
	}

	void Prog::use() const
	{
		gl::UseProgram(uid);
	}

	bool Prog::isInUse() const
	{
		GLint currentProg = 0;
		gl::GetIntegerv(gl::CURRENT_PROGRAM, &currentProg);
    return (currentProg == uid);
	}

	void Prog::stopUsing() const
	{
    if(isInUse())	gl::UseProgram(0);
	}

} //namespace app
