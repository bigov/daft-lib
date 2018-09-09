/**
 * Стартовый файл приложения
 */

#include <stdbool.h>
#include <math.h>
#include <cstring>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rigs.hpp"

/* set directory separator */
#ifdef NIX_OS_TYPE
#define DS "/"
#else /* non _nix - it is MS */
#define DS "\\"
#endif

/* GLSL shaders location */
#define GLSLDIR "glsl"

using namespace std;
const char vfname[] = GLSLDIR DS "cube.v.glsl";
const char ffname[] = GLSLDIR DS "cube.f.glsl";

int	screen_width = 1024, screen_height = 768;
GLuint vbo_cube_vertices, vbo_cube_texcoords;
GLuint ibo_cube_elements;					// global buffer indices
GLuint program;
GLuint texture_id;
GLint attribute_coord3d, attribute_texcoord;
GLint uniform_mvp, uniform_mytexture;

char *base_path;  // путь размещения программы
char pname_vf[256] = {'\0',}; // полный путь к векторному шейдеру
char pname_ff[256] = {'\0',}; // полный путь к фрагментному шейдеру

/* Создание и компиляция шейдерной программы*/
bool init_resources(void)
{
	//  Загрузка расширений OpenGL для работы с GLSL
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
	if(!didLoad) {
		cerr << "ERROR: loading OGL functions.\n" <<
			"Number of functions that failed to load: "
			<< didLoad.GetNumMissing() << endl;
		return false;
	}
	/* загрузка библоитеки SDL2_image  */
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		cerr << "IMG_Init: Failed to init required jpg and png support!"
			<< endl;
		cerr << "IMG_Init: " << IMG_GetError() << endl;
	}

	GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		// top
		-1.0,  1.0,  1.0,
		1.0,  1.0,  1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0,
		// back
		1.0, -1.0, -1.0,
		-1.0, -1.0, -1.0,
		-1.0,  1.0,	-1.0,
		1.0, 1.0, -1.0,
		// bottom
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0, 1.0,
		-1.0,  -1.0, 1.0,
        // left
		-1.0, -1.0, -1.0,
		-1.0, -1.0,  1.0,
		-1.0,  1.0,  1.0,
		-1.0,  1.0, -1.0,
		// right
		1.0, -1.0,  1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		1.0,  1.0,  1.0,
	};

	gl::GenBuffers(1, &vbo_cube_vertices);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_cube_vertices);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(cube_vertices),
			cube_vertices, gl::STATIC_DRAW);

	GLfloat cube_texcoords[2*4*6] = {
		// front
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	};
	for (int i = 1; i < 6; i++)
		memcpy(&cube_texcoords[i*4*2],&cube_texcoords[0],2*4*sizeof(GLfloat));

	gl::GenBuffers(1, &vbo_cube_texcoords);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_cube_texcoords);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(cube_texcoords),
			cube_texcoords, gl::STATIC_DRAW);

	// порядок обхода вершин для построения (треугольниками) сторон куба
	GLushort cube_elements[] = {
		// front
		0,  1,  2,
		2,  3,  0,
		// top
		4,  5,  6,
		6,  7,  4,
		// back
		8,  9, 10,
		10, 11,  8,
		// bottom
		12, 13, 14,
		14, 15, 12,
		// left
		16, 17, 18,
		18, 19, 16,
		// right
		20, 21, 22,
		22, 23, 20,
	};

	gl::GenBuffers(1, &ibo_cube_elements);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(cube_elements),
			cube_elements, gl::STATIC_DRAW);

	/* загрузка текстуры */
	SDL_Surface* res_texture = IMG_Load("res_texture.png");
	if (!res_texture) {
		cerr << "IMG_Load: " << SDL_GetError() << endl;
		return false;
	}

	gl::GenTextures(1, &texture_id);
	gl::BindTexture(gl::TEXTURE_2D, texture_id);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	/* We specify the source format directly for simplicity, but ideally we
	*  should check res_texture->format and possibly pre-convert it to an
	*  OpenGL-supported format. */
	gl::TexImage2D(gl::TEXTURE_2D,  // target
			0,						// level (0 - base, no minimap)
			gl::RGBA,               // internal format
			res_texture->w,			// width
			res_texture->h,         // height
			0,						// border (in OpenGL ES only 0)
			gl::RGBA,				// format
			gl::UNSIGNED_BYTE,		// type
			res_texture->pixels);
	SDL_FreeSurface(res_texture);

	GLuint vs, fs;
	if (!(vs = create_shader(pname_vf, gl::VERTEX_SHADER)))
		return false;
	if (!(fs = create_shader(pname_ff, gl::FRAGMENT_SHADER)))
		return false;
	program = gl::CreateProgram();
	gl::AttachShader(program, vs);
	gl::AttachShader(program, fs);
	gl::LinkProgram(program);
	GLint link_ok = false;
	gl::GetProgramiv(program, gl::LINK_STATUS, &link_ok);
	if (!link_ok) {
		cerr << "Error in gl::LinkProgram." << endl;
		return false;
	}
	const char* attribute_name;
	attribute_name = "coord3d";
	attribute_coord3d = gl::GetAttribLocation(program, attribute_name);
	if (attribute_coord3d == -1) {
		cerr << "Can't bind attribute " << attribute_name << endl;
		return false;
	}
	attribute_name = "texcoord";
	attribute_texcoord = gl::GetAttribLocation(program, attribute_name);
	if (attribute_texcoord == -1) {
		cerr << "Can't bind attribute " << attribute_name << endl;
		return false;
	}
	/* Настройка функций управления матрицей через шейдер */
	const char* uniform_name = "mvp";
	uniform_mvp = gl::GetUniformLocation(program, uniform_name);
	if (uniform_mvp == -1) {
		cerr << "Can't bind unform " << uniform_name << endl;
		return false;
	}
	uniform_name = "mytexture";
	uniform_mytexture = gl::GetUniformLocation(program, uniform_name);
	if (uniform_mytexture == -1) {
		cerr << "Could not bind uniform " << uniform_name << endl;
		return false;
	}
	return true;
}

/* (render) построение изображения */
void onDisplay(SDL_Window * window){

	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	gl::UseProgram(program);

	gl::ActiveTexture(gl::TEXTURE0);
	gl::Uniform1i(uniform_mytexture, 0);
	gl::BindTexture(gl::TEXTURE_2D, texture_id);

	gl::EnableVertexAttribArray(attribute_coord3d);

	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_cube_vertices);
	gl::VertexAttribPointer(
		attribute_coord3d,			// attribute
		3,							// number of elements per vertex
		gl::FLOAT,					// the type of each element
		false,						// take our values as-is
		0,							// next element
		0);							// offset of the first element

	gl::EnableVertexAttribArray(attribute_texcoord);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_cube_texcoords);
	gl::VertexAttribPointer(
		attribute_texcoord, // attribute
		2,                  // number of elements per vertex, here (x,y)
		gl::FLOAT,           // the type of each element
		false,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
	);

	/* рендер куба  */
	int size;
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	gl::GetBufferParameteriv(gl::ELEMENT_ARRAY_BUFFER,
		gl::BUFFER_SIZE, &size);
	gl::DrawElements(gl::TRIANGLES, size/sizeof(GLushort),
		gl::UNSIGNED_SHORT, 0);

	gl::DisableVertexAttribArray(attribute_coord3d);
	gl::DisableVertexAttribArray(attribute_texcoord);
	SDL_GL_SwapWindow(window);
	return;
}

/**
 * Функции управления
 */
void logic(void)
{
	float angle = SDL_GetTicks() / 1000.0 * 15.0; // 15 градусов/секунду

	glm::vec3 axis_x(1, 0, 0);
	glm::vec3 axis_y(0, 1, 0);
	glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_y);
	// anim *= glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_x);

	glm::mat4 model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0, 0.0, -4.0));
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0),
			glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projection = glm::perspective(
			45.0f, 1.0f*screen_width/screen_height, 0.1f, 10.0f);
	glm::mat4 mvp = projection * view * model * anim;

	gl::UniformMatrix4fv(uniform_mvp, 1, false, glm::value_ptr(mvp));
	return;
}

void onResize(int width, int height) {
  screen_width = width;
  screen_height = height;
  gl::Viewport(0, 0, screen_width, screen_height);
  return;
}

/** Цикл отображения окна приложения
 *  пока не появится событие SDL_QUIT
 */
void winDisp(SDL_Window * window)
{
	gl::Enable(gl::BLEND);
	gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
	gl::ClearColor(0.5, 0.69, 1.0, 1.0);
	gl::Enable(gl::DEPTH_TEST);
	gl::DepthFunc(gl::LESS);

	SDL_Event ev;
	SDL_PollEvent(&ev);
	while ( SDL_QUIT != ev.type ) {
		logic();
		onDisplay(window);
		SDL_PollEvent(&ev);

		if (ev.type == SDL_WINDOWEVENT &&
				ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			onResize(ev.window.data1, ev.window.data2);
	}
	return;
}

void free_resources(void)
{
	gl::DeleteProgram(program);
	gl::DeleteBuffers(1, &vbo_cube_vertices);
	gl::DeleteBuffers(1, &vbo_cube_texcoords);
	gl::DeleteBuffers(1, &ibo_cube_elements);
	gl::DeleteTextures(1, &texture_id);
	return;
}

void set_path_dirs()
{
	base_path = SDL_GetBasePath();
	if(base_path) {
		/* текущий каталог размещения программы */
		strcat(pname_vf, base_path);
		strcat(pname_ff, base_path);
	}
	strcat(pname_vf, vfname);		/* полный путь к векторному шейдеру */
	strcat(pname_ff, ffname);		/* --            фрагментному    -- */
	return;
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
		"SDL shaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screen_width,screen_height,SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if(window == NULL) {
		cerr << "Error - can't create window: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	if (SDL_GL_CreateContext(window) == NULL) {
		cerr << "Error - SDL_GL_CreateContext: " << SDL_GetError();
		return EXIT_FAILURE;
	}

	set_path_dirs(); /* настройка файловый путей */

	if (!init_resources()) return EXIT_FAILURE;

	winDisp(window);
	free_resources();
	return EXIT_SUCCESS;
}
