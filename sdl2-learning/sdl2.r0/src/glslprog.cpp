//============================================================================
//
// glslprog.cpp
//
// Класс для создания, настройки шейдерной программы и отображения контента.
//
//============================================================================
#include "glslprog.hpp"
#include <list>
#include <functional>

using std::string;

#define _run std::runtime_error

namespace  lib {
	std::map<string, defShader> defs = 
	{	
    {".ver",  {gl::VERTEX_SHADER, "VERTEX_SHADER"}},
    {".fra",  {gl::FRAGMENT_SHADER, "FRAGMENT_SHADER"}},
/* if OpenGL version > 4
 		{".geo",  {gl::GEOMETRY_SHADER, "GEOMETRY_SHADER"}},
    {".tco",  {gl::TESS_CONTROL_SHADER, "TESS_CONTROL_SHADER"}},
    {".tev",  {gl::TESS_EVALUATION_SHADER, "TESS_EVALUATION_SHADER"}},
    {".cmp",  {gl::COMPUTE_SHADER, "COMPUTE_SHADER"}}
*/
  };

//////////////////////////////////////////////////////////////////////////////

////////
// Конструктор класса
//
VaoPiece::VaoPiece(GLuint v, GLenum m, GLsizei c, GLenum t, const GLvoid * i):
	vao(v), mode(m), count(c), type(t),	indices(i) {}

////////
// Отрисовка элемента по VAO
//
// для OpenGL > 3.1
//void glDrawElementsBaseVertex( GLenum mode, GLsizei count,
//  	GLenum type, GLvoid *indices, GLint basevertex);
//
void VaoPiece::draw(void)
{
	gl::BindVertexArray(vao);
	//gl::DrawElements(mode, count, type, indices);
	gl::DrawElements(gl::TRIANGLE_STRIP, 4,	gl::UNSIGNED_BYTE, nullptr);
	return;	
}

////////
// Получение индекса VAO элемента
//
GLuint VaoPiece::vao_id(void)
{
	return vao;
}

////////
// Деструктор класса
//
VaoPiece::~VaoPiece(void)
{
	gl::DeleteVertexArrays(1, &vao);
	return;
}
//////////////////////////////////////////////////////////////////////////////

////
// Конструктор класса GLSL программы
//
GLSLProgram::GLSLProgram(void) : uniLocs(), attribs(), pieses()
{
	id = gl::CreateProgram();
	if(1 > id) throw _run("Can't create program");
	gl::GetIntegerv(gl::MAJOR_VERSION, &gl_major_ver);
	gl::GetIntegerv(gl::MINOR_VERSION, &gl_minor_ver);

	return;
}
////////
//
//
GLSLProgram::~GLSLProgram()
{
	if(0 == id) return;
	gl::BindBuffer(gl::ARRAY_BUFFER, 0);
	gl::DeleteProgram(id);
	ready = gl::FALSE_;
	id = 0;
	return;
}

////////
// Добавление VAO массива отрисовки четырехугольника в список рендеринга
//
// 	TODO: delete p;
//
void GLSLProgram::listPushFace4v(GLuint VAO)
{
	VaoPiece * p = new VaoPiece(VAO, ModeIdx4, 4,	TypeIdx4, nullptr);
	pieses.push_back(p);
	return;
}

void GLSLProgram::debug_make_area()
{
	//gl::GenVertexArrays(1, &vao);
	//vao_list.push_back(vao);
	//gl::BindVertexArray(vao);
	//gl::EnableVertexAttribArray(0);
	//gl::EnableVertexAttribArray(1);

	// текстурная карта
	float t[] = { 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f };
	float c[12] = {
		-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f
	};

	int x, z;
	for(x = -20; x < 20; x++) for(z = -20; z < 20; z++)
	{
		c[0]  = -0.5f + (float)x,
		c[2]  =  0.5f + (float)z,
		c[3]  =  0.5f + (float)x,
		c[5]  =  0.5f + (float)z,
		c[6]  =  0.5f + (float)x,
		c[8]  = -0.5f + (float)z,
		c[9]  = -0.5f + (float)x,
		c[11] = -0.5f + (float)z;
		
		gl::GenVertexArrays(1, &vao);
		vao_list.push_back(vao);
		gl::BindVertexArray(vao);
		gl::EnableVertexAttribArray(0);
		gl::EnableVertexAttribArray(1);

		pushFace4v(c, t);
	}

	return;
}

////////
// Прием данных для отображения плоского четырехугольника
//
// - массив 3D координат 4-х вершин
// - массив 2D координат 4-х точек текстуры
//
void GLSLProgram::pushFace4v(GLvoid * face4v, GLvoid * texture)
{
	//gl::GenVertexArrays(1, &vao);
	//gl::BindVertexArray(vao);
	GLuint vbo;
	
	// Передать координаты вершин
	gl::GenBuffers(1, &vbo);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, SizeFace4v, face4v, gl::STATIC_DRAW);
	gl::VertexAttribPointer((GLuint)getAttribLocation("coord3d"),
		3, gl::FLOAT, gl::FALSE_, 0, nullptr);

	// Привязать координаты текстуры
	gl::GenBuffers(1, &vbo);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, SizeTex4v, texture, gl::STATIC_DRAW);
	gl::VertexAttribPointer((GLuint)getAttribLocation("texcoord"),
		2, gl::FLOAT, gl::FALSE_, 0, nullptr);

	// Передать в буфер порядок обхода вершин
	gl::GenBuffers(1, &vbo);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, SizeIdx4, Idx4, gl::STATIC_DRAW);

	// добавить VAO прямоугольника Face4v в конвеер отрисовки элементов
	//listPushFace4v(vao);
	//vao_list.push_back(vao);

	return;
}

////////
//
//
GLuint GLSLProgram::handle() { return id; }

////
// получение индекса атрибута по его имени
//
// вначале ищем в служебном массиве. Если не найдено (что маловероятно),
// то пробуем запросить напрямую. В случае неудачи генерируем исключение.
//
GLint GLSLProgram::getAttribLocation(const GLchar * name)
{	
	if(gl::TRUE_ != ready) throw _run("Program not linked yet");

	auto it = attribs.find(name);
	if(it != attribs.end()) return it->second;

	lib::show_error("Error in the function GLSLProgram::getAttribLogation.");

	// попробовать запросить напрямую
	GLint attr = gl::GetAttribLocation(id, name);
	if(-1 == attr) throw _run("Can't get location for: " + (string)name);
  return attr;
}

// Добавление текстуры из файла
void GLSLProgram::addTexture(const string& fn)
{	
	// проверка наличия файла
	struct stat buffer; if (stat(fn.c_str(), &buffer))
		throw _run("missing file: " + fn);

	/* загрузка текстуры */
	SDL_Surface *res_texture = IMG_Load(fn.c_str());
	if (!res_texture)
		throw _run("can't load texture: " + (string)SDL_GetError());
		
	GLuint t;
	gl::GenTextures(1, &t);
	gl::BindTexture(gl::TEXTURE_2D, t);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	/* We specify the source format directly for simplicity, but ideally we
	*  should check res_texture->format and possibly pre-convert it to an
	*  OpenGL-supported format. */
	gl::TexImage2D(gl::TEXTURE_2D,  // target
			0, // level (0 - base, no minimap)
			gl::RGBA, // internal format
			res_texture->w, // width
			res_texture->h, // height
			0, // border (in OpenGL ES only 0)
			gl::RGBA, // format
			gl::UNSIGNED_BYTE, // type
			res_texture->pixels);
	SDL_FreeSurface(res_texture);
	return;
}

////////
// Добавление  из текстового файла в графический конвейер кода шейдера
// 
void GLSLProgram::addShader(const string& fn)
{
	// Определение типа и названия шейдера по расширению имени файла
	// 
	// проверим в списке класса наличие расширения для файла, переданного
	// в параметре. Если нужное расширение в списке отсутствует, то
	// генерируем исключение с сообщением
	auto it = lib::defs.find(getExtension(fn));

	if (it == lib::defs.end())	{
		defShader z = {0, "Wrong extension on the file " + fn};
		throw _run( "can't create shader " + z.name );
	}
	// если расширение известно, то запомним тип и название шейдера
	lib::defShader	d = it->second;
		
	// создать шейдер соответствующего типа
	GLuint _shader = gl::CreateShader(d.id);
	if(0 == _shader) throw _run("Error creating shader " + d.name);
	
	// проверка существования файла шейдера
	struct stat buffer; if (stat(fn.c_str(), &buffer))
		throw _run( "missing file: " + fn + d.name );

	// считать из файла в буфер код шейдера
	size_t nb_read_total = 0, nb_read = 1;
	SDL_RWops * file = SDL_RWFromFile(fn.c_str(), "rb");
	if (file == NULL) throw _run( SDL_GetError() + d.name);

	size_t fsize;
	Sint64 _fsize = SDL_RWsize(file);
	if(_fsize > 0) { fsize = (size_t)_fsize; }
	else { throw _run("Can't read file content " + d.name); }

	GLchar * content =  new GLchar [fsize + 1];
	GLchar * buf = content;
	while (nb_read_total < fsize && nb_read != 0)
	{
		nb_read = SDL_RWread(file, buf, 1, (fsize - nb_read_total));
		nb_read_total += nb_read;
		buf += nb_read;
	}
	SDL_RWclose(file);
	if (nb_read_total != fsize)
	{
		delete [] content;
		throw _run("Error reading file " + fn + d.name);
	}
	content[nb_read_total] = '\0';
	// скомпилировать шейдер
	const GLchar * codeArray[] = {content, };
	gl::ShaderSource(_shader, 1, codeArray, NULL);
	gl::CompileShader(_shader);

	// освободить память буфера
	delete [] content;

	attachShader(_shader);
	return;
}

////
// компиляция GLSL шейдеров
//
void GLSLProgram::attachShader(GLuint _shader)
{	
	checkShader(_shader);
	gl::AttachShader(id, _shader);
	return;
}

////
// Проверка результата компиляции шейдера
//
// при наличии ошибки генерируется исключение
//
void GLSLProgram::checkShader(GLuint _shader)
{
	GLint compile_result;
	gl::GetShaderiv(_shader, gl::COMPILE_STATUS, &compile_result);
	if(!compile_result)
		throw _run("Fail compile shader,\n" + getShaderInfoLog(_shader));
	return;
}

// Выделение "расширения" из строки с именем файла - подстроки от последней
// точки в имени до конца строки.
string GLSLProgram::getExtension(const string& fn)
{
  size_t loc = fn.find_last_of('.');
  if( loc != string::npos ) {
    return fn.substr(loc, string::npos);
  }
  return "";
}

////
// Выбор информации об ошибках в программе GLSL
//
string GLSLProgram::getShaderInfoLog(GLuint shader_id)
{
	string log_info = "No more information";
	GLint logLen;
	gl::GetShaderiv(shader_id, gl::INFO_LOG_LENGTH, &logLen);
	if(logLen > 1)
	{
		char * log = new char[logLen];
		GLsizei written;
		gl::GetShaderInfoLog(shader_id, logLen, &written, log);
		log_info = (string)log;
		delete [] log;
	}
	return log_info;
}

////
// Выбор информации об ошибках в программе GLSL
//
string GLSLProgram::getProgramInfoLog()
{
	string log_info = "No more information";
	GLint logLen;
	gl::GetProgramiv(id, gl::INFO_LOG_LENGTH, &logLen);
	if(logLen >1)
	{
		char * log = new char[logLen];
		GLsizei written;
		gl::GetProgramInfoLog(id, logLen, &written, log);
		log_info = (string)log;
		delete [] log;
	}
	return log_info;
}

////////
//
//
void GLSLProgram::link()
{
	if(gl::TRUE_ == ready) throw _run("Recall link() procedure");
	gl::LinkProgram(id);
	int status;
	gl::GetProgramiv(id, gl::LINK_STATUS, (int *)&status);
	if(0 == status) 
		throw _run("Fail link program,\n" + getProgramInfoLog());
	ready = gl::TRUE_;
	
	// Очистка списка активных атрибутов шейдерной программы
	attribs.clear();
	// и заполнение
	if(((4 == gl_major_ver) && (gl_minor_ver > 2)) || (gl_major_ver > 4))
		fillAttribsList_modern();
	else
		fillAttribsList();

	return;
}

////
//	Отрисовка примитивов, привязанных через VAO
//	TODO: сделать вывод сообщений об ошибках через обработчик исключений
//
void GLSLProgram::draw()
{
	//std::list<VaoPiece>::const_iterator p;
	//for_each(pieses.begin(), pieses.end(), std::mem_fun(&VaoPiece::draw));

	for(auto VAO: vao_list)
	{
		gl::BindVertexArray(VAO);
		gl::DrawElements(gl::TRIANGLE_STRIP, 4,	gl::UNSIGNED_BYTE, nullptr);
	}
	return;
}

////
// Заполнение списка активных атрибутов и их индексов для OpenGL > 4.2
//
// выполняется после линковки GLSL программы
//
void GLSLProgram::fillAttribsList_modern()
{
	fillAttribsList();
	return;
	//ONLY! for GL >= 4.3
	// TODO
/*
	GLint in; // запросить количество активных атрибутов
	GLuint un;
	gl::GetProgramInterfaceiv(id, gl::PROGRAM_INPUT, gl::ACTIVE_RESOURCES, &in);
	if(in < 1) throw Flaw("Err on calling gl::GetProgramInterfaceiv");
	
	un = GLuint(in);
	GLenum props[] = {gl::NAME_LENGTH, gl::TYPE, gl::LOCATION};
	for(GLuint i = 0; i < un; ++i)
	{
		GLint results[3];
		// получить параметры каждого атрибута
		gl::GetProgramResourceiv(id, gl::PROGRAM_INPUT, i, 3, props,
			3, NULL, results);

		// получить имя каждого атрибута
		GLint n_size = results[0] + 1;
		char * name = new char[n_size];
		gl::GetProgramResourceName(id, gl::PROGRAM_INPUT, i, n_size, NULL, name);

		//заполнить массив (map)
		attribs[name] = results[2];
		delete [] name;
	}
	return;
	*/
}

////
// Заполнение списка атрибутов и их индексов для OpenGL < 4.3
//
void GLSLProgram::fillAttribsList()
{
	GLuint count;
	GLint safe_count;
	gl::GetProgramiv(id, gl::ACTIVE_ATTRIBUTES, &safe_count);
	if(safe_count < 1) throw _run("Can't fill Attribs List");
	else count = (GLuint)safe_count;

	GLsizei bufSize;
	gl::GetProgramiv(id, gl::ACTIVE_ATTRIBUTE_MAX_LENGTH, &bufSize);
	GLchar * name = new char [bufSize];
	GLsizei length;
	GLint size;
	GLenum type;
	GLint alc;
	for(GLuint i = 0; i < count; ++i)
	{
		gl::GetActiveAttrib (id, i, bufSize, &length, &size, &type, name);
		alc = gl::GetAttribLocation(id, name);
		if(-1 == alc) throw _run("Can't get location for: " + (string)name);
		attribs[name] = alc;
	}
	delete [] name;

	return;
}

void GLSLProgram::use()
{
	if(ready != gl::TRUE_) link();
	gl::UseProgram(id);
	return;
}

GLint GLSLProgram::getUniformLocation(const GLchar * name )
{
	GLint i;
	gl::GetIntegerv(gl::CURRENT_PROGRAM, &i);
	if((GLuint)i != id) throw _run("Program not yet use");

  std::map<std::string, int>::iterator pos;
  pos = uniLocs.find(name);

  if( pos == uniLocs.end() ) {
		GLint l = gl::GetUniformLocation(id, name);
		if(0 > l) throw _run("Not found uniform name: " + (string)name);
    uniLocs[name] = l;
	}

  return uniLocs[name];
}

void GLSLProgram::setUniform( const GLchar *name, bool val )
{
	GLint loc;
	loc = getUniformLocation(name);
	gl::Uniform1i(loc, val);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, GLint val )
{
 	GLint loc;
	loc = getUniformLocation(name);
  gl::Uniform1i(loc, val);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, GLuint val )
{
	GLint loc;
	loc = getUniformLocation(name);
  gl::Uniform1ui(loc, val);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, float val )
{
	GLint loc;
	loc = getUniformLocation(name);
  gl::Uniform1f(loc, val);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, float x, float y, float z)
{
	GLint loc;
	loc = getUniformLocation(name);

  gl::Uniform3f(loc, x, y, z);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, const vec2 & v)
{
	GLint loc;
	loc = getUniformLocation(name);
  gl::Uniform2f(loc, v.x, v.y);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, const vec3 & v)
{
	setUniform(name, v.x, v.y, v.z);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, const vec4 & v)
{
	GLint loc;
	loc = getUniformLocation(name);
  gl::Uniform4f(loc, v.x, v.y, v.z, v.w);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, const mat3 & m)
{
	GLint loc;
	loc = getUniformLocation(name);
  gl::UniformMatrix3fv(loc, 1, gl::FALSE_, &m[0][0]);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, const mat4 & m)
{
	GLint loc;
	loc = getUniformLocation(name);
  gl::UniformMatrix4fv(loc, 1, gl::FALSE_, &m[0][0]);
	return;
}

} //namespace lib

/*************************************************************************
	//// Заполнение массива переменных Uniforms:
	//
	//// получить количество
	//glGetObjectParameteriv (shaderID, GL_ACTIVE_UNIFORMS, &count);
	//
	//// в цикле запросить for i in 0 to count:
	//glGetActiveUniform (shaderID, i, bufSize, &length, &size, &type, name);
*/

/*************************************************************************
 
 // Создание и настройки буфера для блока uniform переменных шейдера
	GLint blockIndex = gl::GetUniformBlockIndex(programHandle, "BlobSettings");
	if(blockIndex < 0) show_err_box("Can't get blockIndex");
	
	GLint blockSize;
	gl::GetActiveUniformBlockiv(programHandle, blockIndex,
		gl::UNIFORM_BLOCK_DATA_SIZE, &blockSize);

	GLubyte * blockBuffer;
	blockBuffer = (GLubyte *) malloc(blockSize);

	const GLchar * names[] = { "BlobSettings.InnerColor",
		"BlobSettings.OuterColor", "BlobSettings.RadiusInner",
		"BlobSettings.RadiusOuter"};
	
	GLuint indices[4];
	gl::GetUniformIndices(programHandle, 4, names, indices);

	GLint offset[4];
	gl::GetActiveUniformsiv(programHandle, 4, indices,
		gl::UNIFORM_OFFSET, offset);

	// Запись данных в буфер

	GLfloat outerColor[] = {0.5f, 0.69f, 1.0f, 1.0f};
	GLfloat innerColor[] = {1.0f, 1.0f, 0.75f, 1.0f};
	GLfloat innerRad = 0.20f, outerRad = 0.35f;

	memcpy(blockBuffer + offset[0], innerColor, 4 * sizeof(GLfloat));
	memcpy(blockBuffer + offset[1], outerColor, 4 * sizeof(GLfloat));
	memcpy(blockBuffer + offset[2], &innerRad, sizeof(GLfloat));
	memcpy(blockBuffer + offset[3], &outerRad, sizeof(GLfloat));

	// Передача данных в буферный объект
	GLuint uboHandl;
	gl::GenBuffers( 1, &uboHandl);
	gl::BindBuffer(gl::UNIFORM_BUFFER, uboHandl);
	gl::BufferData(gl::UNIFORM_BUFFER, blockSize, blockBuffer, gl::DYNAMIC_DRAW);
	gl::BindBufferBase(gl::UNIFORM_BUFFER, 1, uboHandl);

 */
