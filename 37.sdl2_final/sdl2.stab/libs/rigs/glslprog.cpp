//============================================================================
//
// glslprog.cpp
//
// Класс для создания и настройки шейдерной программы
//
//============================================================================

#include "glslprog.hpp"

using std::string;

namespace Rigs {
	std::map<string, defShader> defs = 
	{	
    {".ver",  {gl::VERTEX_SHADER, "VERTEX_SHADER"}},
    {".geo",  {gl::GEOMETRY_SHADER, "GEOMETRY_SHADER"}},
    {".tco",  {gl::TESS_CONTROL_SHADER, "TESS_CONTROL_SHADER"}},
    {".tev",  {gl::TESS_EVALUATION_SHADER, "TESS_EVALUATION_SHADER"}},
    {".fra",  {gl::FRAGMENT_SHADER, "FRAGMENT_SHADER"}},
    {".cmp",  {gl::COMPUTE_SHADER, "COMPUTE_SHADER"}}
  };
} //namespace Rigs

//////////////////////////////////////////////////////////////////////////////

errGLSL::errGLSL(string m) : err(m) { }
string errGLSL::what() { return err; }

errShader::errShader(string m, Rigs::defShader d)	: errGLSL(m), def(d) { }
string errShader::what() { return def.name +": " + err; }

errProgram::errProgram(string m) : errGLSL(m) { }

//////////////////////////////////////////////////////////////////////////////

////
// Класс GLSL программа
//
//
GLSLProgram::GLSLProgram() throw(errProgram) : id(0), ready(gl::FALSE_)
{
	vbo_count = 0;
	vbo = NULL;
	id = gl::CreateProgram();
	if(1 > id) throw errProgram("Can't create program");
	gl::GetIntegerv(gl::MAJOR_VERSION, &gl_major_ver);
	gl::GetIntegerv(gl::MINOR_VERSION, &gl_minor_ver);
	return;
}

GLSLProgram::~GLSLProgram()
{
	if(0 == id) return;
	if(vbo != NULL) delete [] vbo;
	vbo_count = 0;
	gl::BindBuffer(gl::ARRAY_BUFFER, 0);
	gl::DeleteProgram(id);
	ready = gl::FALSE_;
	id = 0;
	return;
}

GLuint GLSLProgram::handle() { return id; }

////
// получение индекса атрибута по его имени
//
// вначале ищем в служебном массиве. Если не найдено (что маловероятно),
// то пробуем запросить напрямую. В случае неудачи генерируем исключение.
//
GLint GLSLProgram::getAttribLocation(const GLchar * name) throw(errProgram)
{	
	if(gl::TRUE_ != ready) throw errProgram("Program not linked yet");

	auto it = attribs.find(name);
	if(it != attribs.end()) return it->second;

	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		"Error in the function GLSLProgram::getAttribLogation.");

	// попробовать запросить напрямую
	GLint attr = gl::GetAttribLocation(id, name);
	if(-1 == attr) throw errProgram("Can't get location for: " + (string)name);
  return attr;
}

// Добавление текстуры из файла
void GLSLProgram::addTexture(const string& fn) throw(errProgram)
{	
	// проверка наличия файла
	struct stat buffer; if (stat(fn.c_str(), &buffer))
		throw errProgram("missing file: " + fn);

	/* загрузка текстуры */
	SDL_Surface *res_texture = IMG_Load(fn.c_str());
	if (!res_texture)
		throw errProgram("can't load texture: " + (string)SDL_GetError());
		
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

// Добавление  из текстового файла в графический конвейер кода шейдера
void GLSLProgram::addShader(const string& fn) throw(errShader)
{
	Rigs::defShader d;

	// Определение типа и названия шейдера по расширению имени файла
	// 
	// проверим в списке класса наличие расширения для файла, переданного
	// в параметре. Если нужное расширение в списке отсутствует, то
	// генерируем исключение с сообщением
	auto it = Rigs::defs.find(getExtension(fn));
	if (it == Rigs::defs.end())	{
		d = {0, "[" + fn + "] wrong extension of file"};
		throw errShader( "can't create shader", d );
	}	else {
	// если расширение известно, то запомним тип и название шейдера
		d = it->second;
	}
	// создать шейдер соответствующего типа
	GLuint _shader = gl::CreateShader(d.id);
	if(0 == _shader) throw errShader("Error creating shader", d);
	
	// проверка существования файла шейдера
	struct stat buffer; if (stat(fn.c_str(), &buffer))
		throw errShader( "missing file: " + fn, d );

	// считать из файла в буфер код шейдера
	Sint64 nb_read_total = 0, nb_read = 1;
	SDL_RWops * file = SDL_RWFromFile(fn.c_str(), "rb");
	if (file == NULL) throw errShader( SDL_GetError(), d);
	Sint64 fsize = SDL_RWsize(file);
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
		delete [] content; throw errShader("Error reading file " + fn, d);
	}
	content[nb_read_total] = '\0';
	// скомпилировать шейдер
	const GLchar * codeArray[] = {content, };
	gl::ShaderSource(_shader, 1, codeArray, NULL);
	gl::CompileShader(_shader);

	// освободить память буфера
	delete [] content;

	try { attachShader(_shader); }
	catch(errGLSL& e ) {
		throw errShader(e.what() + "\nin the file: " + fn, d);
	}

	return;
}

////
// компиляция GLSL шейдеров
//
void GLSLProgram::attachShader(GLuint _shader) throw(errGLSL)
{	
	
	try	{ checkShader(_shader); } 
	catch (errGLSL& e ) { throw errGLSL(e.what()); }

	gl::AttachShader(id, _shader);
	return;
}

////
// Проверка результата компиляции шейдера
//
// при наличии ошибки генерируется исключение
//
void GLSLProgram::checkShader(GLuint _shader) throw(errGLSL)
{
	GLint compile_result;
	gl::GetShaderiv(_shader, gl::COMPILE_STATUS, &compile_result);
	if(!compile_result)
		throw errGLSL("Fail compile shader,\n" + getShaderInfoLog(_shader));
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

void GLSLProgram::link() throw (errProgram)
{
	if(gl::TRUE_ == ready) throw errProgram("Recall link() procedure");
	gl::LinkProgram(id);
	GLint status;
	gl::GetProgramiv(id, gl::LINK_STATUS, &status);
	if(gl::TRUE_ != status) 
		throw errProgram("Fail link program,\n" + getProgramInfoLog());
	ready = gl::TRUE_;
	
	// Очистка списка активных атрибутов шейдерной программы
	attribs.clear();
	// и заполнение
	if(((4 == gl_major_ver) && (gl_minor_ver > 2)) || (gl_major_ver > 4))
	{
		try {fillAttribsList_modern();}
		catch(errGLSL & e) { throw errProgram(e.what()); }
	}
	else
	{
		try {fillAttribsList();}
		catch(errGLSL & e) { throw errProgram(e.what()); }
	}
	genVBO();
	return;
}

void GLSLProgram::genVBO() 
{
	gl::GenVertexArrays(1, &vao);
	gl::BindVertexArray(vao);

	// Число массивов для записи в VBO сгенерируем по числу входных атрибутов
	vbo_count = attribs.size();
	for(GLint i = 0; i < vbo_count; ++i) gl::EnableVertexAttribArray(i);
	
	vbo = new GLuint[vbo_count];
	gl::GenBuffers(vbo_count, vbo);
}

////
// Передача данных в атрибуты шейдеров
//
//		name  - name of attribute
//  	per_v - number of components per vertex attribute
//  	data  - array of data
//  	count - num elements in the array
//
void GLSLProgram::setAttrib(const GLchar * name, GLint per_v,
	const GLfloat * data, GLuint count) throw (errProgram)
{
	// Значения по-умолчанию
	GLboolean normalized = gl::FALSE_;
	GLsizei stride = 0;
	const GLvoid * offset = (GLubyte *)NULL;

	setBufferData(count*sizeof(GLfloat), data);

	GLuint attr; try {	attr = getAttribLocation(name); }
	catch (errProgram & e) { throw errProgram(e.what()); }

	gl::VertexAttribPointer(attr, per_v, gl::FLOAT, normalized, stride, offset);

	return;
}

////
// передача атрибутов шейдеров в буфер
//
void GLSLProgram::setBufferData(GLsizeiptr size, const GLvoid * data)
	throw (errProgram)
{
	GLenum target = gl::ARRAY_BUFFER;
	GLenum mode = gl::STATIC_DRAW;

	vbo_count -= 1;
	if(0 > vbo_count) throw errProgram("VBO index failure");
	gl::BindBuffer(target, vbo[vbo_count]);
	gl::BufferData(target, size, data, mode);
	return;
}

////
// Передача в буфер данных индекса
//
// для передачи порядка обхода вершин при рисовании примитивов.
//
void GLSLProgram::setBufferIndex(const GLuint * data, GLuint count)
	throw (errProgram)
{
	GLenum target = gl::ELEMENT_ARRAY_BUFFER;
	GLenum usage = gl::STATIC_DRAW;

	// Запомнить в классовой переменной число индексов для использования
	// в процедуре рисования примитивов
	indexes = count;

	GLuint idx_id;
  gl::GenBuffers( 1, &idx_id );
	gl::BindBuffer(target, idx_id);
	gl::BufferData(target, count*sizeof(GLuint), data, usage);
	
	return;
}
////
//	Отрисовка примитива
//
void GLSLProgram::draw()
{
	gl::BindVertexArray(vao);
	gl::DrawElements(gl::TRIANGLE_STRIP, indexes, gl::UNSIGNED_INT, NULL);

	return;
}

////
// Заполнение списка активных атрибутов и их индексов для OpenGL > 4.2
//
// выполняется после линковки GLSL программы
//
void GLSLProgram::fillAttribsList_modern() throw(errGLSL)
{
	try { fillAttribsList(); }
	catch (errGLSL & e) { throw errGLSL(e.what()); }
	return;

	//ONLY! for GL >= 4.3

	GLint n; // запросить количество активных атрибутов
	gl::GetProgramInterfaceiv(id, gl::PROGRAM_INPUT, gl::ACTIVE_RESOURCES, &n);
	if(n < 1) throw errGLSL("Err on calling gl::GetProgramInterfaceiv");

	GLenum props[] = {gl::NAME_LENGTH, gl::TYPE, gl::LOCATION};
	for(GLint i = 0; i < n; ++i)
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
}

////
// Заполнение списка атрибутов и их индексов для OpenGL < 4.3
//
void GLSLProgram::fillAttribsList() throw(errGLSL)
{
	GLint count;
	gl::GetProgramiv(id, gl::ACTIVE_ATTRIBUTES, &count);
	if(count < 1) throw errGLSL("Can't fill Attribs List");

	GLsizei bufSize;
	gl::GetProgramiv(id, gl::ACTIVE_ATTRIBUTE_MAX_LENGTH, &bufSize);
	GLchar * name = new char [bufSize];
	GLsizei length;
	GLint size;
	GLenum type;
	GLint alc;
	for(GLint i = 0; i < count; ++i)
	{
		gl::GetActiveAttrib (id, i, bufSize, &length, &size, &type, name);
		alc = gl::GetAttribLocation(id, name);
		if(-1 == alc) throw errGLSL("Can't get location for: " + (string)name);
		attribs[name] = alc;
	}
	delete [] name;

	return;
}

void GLSLProgram::use() throw(errProgram)
{
	if(ready != gl::TRUE_) link();
	gl::UseProgram(id);
	return;
}

GLint GLSLProgram::getUniformLocation(const GLchar * name ) throw(errProgram)
{
	GLint i;
	gl::GetIntegerv(gl::CURRENT_PROGRAM, &i);
	if((GLuint)i != id) throw errProgram("Program not yet use");

  std::map<std::string, int>::iterator pos;
  pos = uniLocs.find(name);

  if( pos == uniLocs.end() ) {
		GLint l = gl::GetUniformLocation(id, name);
		if(0 > l) throw errProgram("Not found uniform name: " + (string)name);
    uniLocs[name] = l;
	}

  return uniLocs[name];
}

void GLSLProgram::setUniform( const GLchar *name, bool val )
	throw(errProgram)
{
	GLint loc;
  try{loc = getUniformLocation(name);}
	catch(errProgram & e) {throw errProgram(e.what());}

	gl::Uniform1i(loc, val);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, GLint val )
	throw(errProgram)
{
 	GLint loc;
  try{loc = getUniformLocation(name);}
	catch(errProgram & e) {throw errProgram(e.what());}

  gl::Uniform1i(loc, val);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, GLuint val )
	throw(errProgram)
{
	GLint loc;
  try{loc = getUniformLocation(name);}
	catch(errProgram & e) {throw errProgram(e.what());}

  gl::Uniform1ui(loc, val);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, float val )
	throw(errProgram)
{
	GLint loc;
  try{loc = getUniformLocation(name);}
	catch(errProgram & e) {throw errProgram(e.what());}

  gl::Uniform1f(loc, val);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, float x, float y, float z)
	throw(errProgram)
{
	GLint loc;
  try{loc = getUniformLocation(name);}
	catch(errProgram & e) {throw errProgram(e.what());}

  gl::Uniform3f(loc, x, y, z);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, const vec2 & v)
	throw(errProgram)
{
	GLint loc;
  try{loc = getUniformLocation(name);}
	catch(errProgram & e) {throw errProgram(e.what());}

  gl::Uniform2f(loc, v.x, v.y);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, const vec3 & v)
	throw(errProgram)
{
	try{ setUniform(name, v.x, v.y, v.z); }
	catch(errProgram & e) {throw errProgram(e.what());}
	return;
}

void GLSLProgram::setUniform( const GLchar *name, const vec4 & v)
	throw(errProgram)
{
	GLint loc;
  try{loc = getUniformLocation(name);}
	catch(errProgram & e) {throw errProgram(e.what());}

  gl::Uniform4f(loc, v.x, v.y, v.z, v.w);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, const mat3 & m)
	throw(errProgram)
{
	GLint loc;
  try{loc = getUniformLocation(name);}
	catch(errProgram & e) {throw errProgram(e.what());}

  gl::UniformMatrix3fv(loc, 1, gl::FALSE_, &m[0][0]);
	return;
}

void GLSLProgram::setUniform( const GLchar *name, const mat4 & m)
	throw(errProgram)
{
	GLint loc;
  try{loc = getUniformLocation(name);}
	catch(errProgram & e) {throw errProgram(e.what());}

  gl::UniformMatrix4fv(loc, 1, gl::FALSE_, &m[0][0]);
	return;
}


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
