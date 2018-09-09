/**
 * From the OpenGL Programming wikibook: http://en.wikibooks.org/wiki/OpenGL_Programming
 * This file is in the public domain.
 * Contributors: Sylvain Beucler
 */

#include <stdio.h>
#include <stdlib.h>
#include "gl_core_3_0.hpp"

/**
 * Store all the file's contents in memory, useful to pass shaders
 * source code to OpenGL
 */
char* file_read(const char* filename)
{
	FILE* in = fopen(filename, "rb");
	if (in == NULL) return NULL;

	int res_size = BUFSIZ;
	char* res = (char*)malloc(res_size);
	int nb_read_total = 0;

	while (!feof(in) && !ferror(in)) {
		if (nb_read_total + BUFSIZ > res_size) {
			if (res_size > 10*1024*1024) break;
			res_size = res_size * 2;
			res = (char*)realloc(res, res_size);
		}
		char* p_res = res + nb_read_total;
		nb_read_total += fread(p_res, 1, BUFSIZ, in);
	}

	fclose(in);
	res = (char*)realloc(res, nb_read_total + 1);
	res[nb_read_total] = '\0';
	return res;
}

/**
 * Display compilation errors from the OpenGL shader compiler
 */
void print_log(GLuint object)
{
	GLint log_length = 0;
	if (gl::IsShader(object))
		gl::GetShaderiv(object, gl::INFO_LOG_LENGTH, &log_length);
	else if (gl::IsProgram(object))
		gl::GetProgramiv(object, gl::INFO_LOG_LENGTH, &log_length);
	else {
		fprintf(stderr, "printlog: Not a shader or a program\n");
		return;
	}

	char* log = (char*)malloc(log_length);

	if (gl::IsShader(object))
		gl::GetShaderInfoLog(object, log_length, NULL, log);
	else if (gl::IsProgram(object))
		gl::GetProgramInfoLog(object, log_length, NULL, log);

	fprintf(stderr, "%s", log);
	free(log);
}

/**
 * Compile the shader from file 'filename', with error handling
 */
GLuint create_shader(const char* filename, GLenum type)
{
	const GLchar* source = file_read(filename);
	if (source == NULL) {
		fprintf(stderr, "Error opening %s: ", filename); perror("");
		return 0;
	}
	GLuint res = gl::CreateShader(type);
	const GLchar* sources[] = {
    // Define GLSL version
#ifdef GL_ES_VERSION_2_0
    "#version 100\n"  // OpenGL ES 2.0
#else
    "#version 120\n"  // OpenGL 2.1
#endif
    ,
    // GLES2 precision specifiers
#ifdef GL_ES_VERSION_2_0
    // Define default float precision for fragment shaders:
    (type == GL_FRAGMENT_SHADER) ?
    "#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
    "precision highp float;           \n"
    "#else                            \n"
    "precision mediump float;         \n"
    "#endif                           \n"
    : ""
    // Note: OpenGL ES automatically defines this:
    // #define GL_ES
#else
    // Ignore GLES 2 precision specifiers:
    "#define lowp   \n"
    "#define mediump\n"
    "#define highp  \n"
#endif
    ,
    source };
	gl::ShaderSource(res, 3, sources, NULL);
	free((void*)source);

	gl::CompileShader(res);
	GLint compile_ok = false;
	gl::GetShaderiv(res, gl::COMPILE_STATUS, &compile_ok);
	if (!compile_ok) {
		fprintf(stderr, "%s:", filename);
		print_log(res);
		gl::DeleteShader(res);
		return 0;
	}

  return res;
}

GLuint create_program(const char *vertexfile, const char *fragmentfile) {
	GLuint program = gl::CreateProgram();
	GLuint shader;

	if(vertexfile) {
		shader = create_shader(vertexfile, gl::VERTEX_SHADER);
		if(!shader)
			return 0;
		gl::AttachShader(program, shader);
	}

	if(fragmentfile) {
		shader = create_shader(fragmentfile, gl::FRAGMENT_SHADER);
		if(!shader)	return 0;
		gl::AttachShader(program, shader);
	}

	gl::LinkProgram(program);
	GLint link_ok = false;
	gl::GetProgramiv(program, gl::LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "gl::LinkProgram:");
		print_log(program);
		gl::DeleteProgram(program);
		return 0;
	}

	return program;
}

#ifdef GL_GEOMETRY_SHADER
GLuint create_gs_program(const char *vertexfile, const char *geometryfile,
	const char *fragmentfile, GLint input, GLint output, GLint vertices) {
		GLuint program = glCreateProgram();
		GLuint shader;

	if(vertexfile) {
		shader = create_shader(vertexfile, GL_VERTEX_SHADER);
		if(!shader)
			return 0;
		glAttachShader(program, shader);
	}

	if(geometryfile) {
		shader = create_shader(geometryfile, GL_GEOMETRY_SHADER);
		if(!shader)
			return 0;
		glAttachShader(program, shader);

		glProgramParameteriEXT(program, GL_GEOMETRY_INPUT_TYPE_EXT, input);
		glProgramParameteriEXT(program, GL_GEOMETRY_OUTPUT_TYPE_EXT, output);
		glProgramParameteriEXT(program, GL_GEOMETRY_VERTICES_OUT_EXT, vertices);
	}

	if(fragmentfile) {
		shader = create_shader(fragmentfile, GL_FRAGMENT_SHADER);
		if(!shader)
			return 0;
		glAttachShader(program, shader);
	}

	glLinkProgram(program);
	GLint link_ok = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		print_log(program);
		glDeleteProgram(program);
		return 0;
	}
	return program;
}
#else
GLuint create_gs_program(const char *vertexfile, const char *geometryfile,
	const char *fragmentfile, GLint input, GLint output, GLint vertices) {
	fprintf(stderr, "Missing support for geometry shaders.\n");
	return 0;
}
#endif

GLint get_attrib(GLuint program, const char *name) {
	GLint attribute = gl::GetAttribLocation(program, name);
	if(attribute == -1)
		fprintf(stderr, "Could not bind attribute %s\n", name);
	return attribute;
}

GLint get_uniform(GLuint program, const char *name) {
	GLint uniform = gl::GetUniformLocation(program, name);
	if(uniform == -1)
		fprintf(stderr, "Could not bind uniform %s\n", name);
	return uniform;
}
