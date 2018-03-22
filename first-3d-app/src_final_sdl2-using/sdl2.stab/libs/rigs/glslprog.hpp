//============================================================================
//
// glslprog.hpp
//
//============================================================================

#ifndef GLSLPROG_H
#define GLSLPROG_H

#include "../common.hpp"

using std::string;
using glm::mat3;
using glm::mat4;
using glm::vec2;
using glm::vec3;
using glm::vec4;

namespace Rigs
{
  struct defShader { GLenum id; string name; };
} //namespace Rigs

// Группировка ошибок GLSL
class errGLSL
{
	protected:
		string err;
	public:
		errGLSL(string err_message);
		virtual ~errGLSL(void) {};
		virtual string what(void);
};

// Ошибки компиляции шейдеров
class errShader : public errGLSL
{
	protected:
		Rigs::defShader def;
	public:
		errShader(string err_message, Rigs::defShader define);
		virtual ~errShader(void) {};
		virtual string what(void);
};

// Ошибки компиляции GLSL программы
class errProgram : public errGLSL
{
	public:
		errProgram(string err_message);
};

class GLSLProgram
{
	public:
		GLSLProgram() throw(errProgram);
		~GLSLProgram();
		void addShader(const string& fileName) throw(errShader);
		void addTexture(const string& fn) throw(errProgram);
		void use() throw (errProgram);
		GLuint handle();
		void link() throw(errProgram);
		void genVBO();
		GLint getAttribLocation(const GLchar * name) throw(errProgram);
		void setBufferData(GLsizeiptr sizeptr, const GLvoid * data)
			throw (errProgram);
		void setBufferIndex(const GLuint * data, GLuint count) throw (errProgram);
		void setAttrib(const GLchar * name, GLint per_v, const GLfloat * data,
			GLuint count) throw (errProgram);
		void setUniform( const GLchar *name, bool val ) throw(errProgram);
		void setUniform( const GLchar *name, GLint val ) throw(errProgram);
		void setUniform( const GLchar *name, GLuint val ) throw(errProgram);
		void setUniform( const GLchar *name, float val ) throw(errProgram);
		void setUniform( const GLchar *name, float x,float y,float z)
			throw(errProgram);
		void setUniform( const GLchar *name, const vec2 & v) throw(errProgram);
		void setUniform( const GLchar *name, const vec3 & v) throw(errProgram);
		void setUniform( const GLchar *name, const vec4 & v) throw(errProgram);
		void setUniform( const GLchar *name, const mat3 & m) throw(errProgram);
		void setUniform( const GLchar *name, const mat4 & m) throw(errProgram);
		void draw();
	
	private:
		GLuint vao;
		GLuint * vbo;
		int vbo_count;
		GLint gl_major_ver;
		GLint gl_minor_ver;
		GLuint id;
		GLboolean ready;
		GLuint indexes; // num of indexes for draw primitive
    std::map<string, GLint> uniLocs; // set of uniformLocations
    std::map<string, GLint> attribs; // set of attribs indexes
		void fillAttribsList_modern(void) throw(errGLSL);
		void fillAttribsList(void) throw(errGLSL);
		string getExtension(const string& file_name);
		void attachShader(GLuint _shader) throw(errGLSL);
		void checkShader(GLuint shader_handle) throw(errGLSL);
		GLint getUniformLocation(const GLchar * name ) throw(errProgram);
		string getProgramInfoLog();
		string getShaderInfoLog(GLuint shader_id);
};

#endif // GLSLPROG_H
