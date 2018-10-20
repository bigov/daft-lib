/**
 * Стартовый файл приложения
 */

#include <stdbool.h>
#include <math.h>

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
GLuint program;
GLint attribute_coord3d, attribute_v_color;
GLint uniform_mvp, uniform_m_transform;
struct attributes {	GLfloat coord3d[3];	GLfloat v_color[3]; };
GLuint vbo_cube_vertices, vbo_cube_colors;  // global buffer handles
GLuint ibo_cube_elements;					// global buffer indices

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

	GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0,
	};

	gl::GenBuffers(1, &vbo_cube_vertices);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_cube_vertices);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(cube_vertices),
			cube_vertices, gl::STATIC_DRAW);

	GLfloat cube_colors[] = {
		// front colors
		0.0, 0.0, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.0, 0.0,
		0.0, 0.8, 0.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	};

	gl::GenBuffers(1, &vbo_cube_colors);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_cube_colors);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(cube_colors),
			cube_colors, gl::STATIC_DRAW);

	// порядок обхода вершин для построения (треугольниками) сторон куба
	GLushort cube_elements[] = {
		0, 1, 2, 3, 0, 2,	// front
		3, 2, 6, 7, 3, 6,	// top
		7, 6, 5, 4, 7, 5,	// back
		4, 5, 1, 0, 4, 1,	// bottom
		4, 0, 3, 7, 4, 3,	// left
		1, 5, 6, 2, 1, 6,	// right
	};

	gl::GenBuffers(1, &ibo_cube_elements);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(cube_elements),
			cube_elements, gl::STATIC_DRAW);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);

	GLuint vs, fs;
	if (!(vs = create_shader(vfname, gl::VERTEX_SHADER))) return false;
	if (!(fs = create_shader(ffname, gl::FRAGMENT_SHADER))) return false;

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

	attribute_name = "v_color";
	attribute_v_color = gl::GetAttribLocation(program, attribute_name);
	if (attribute_v_color == -1) {
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

	return true;
}

/* (render) построение изображения */
void onDisplay(SDL_Window * window)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	gl::UseProgram(program);

	gl::EnableVertexAttribArray(attribute_coord3d);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_cube_vertices);
	gl::VertexAttribPointer(
		attribute_coord3d,			// attribute
		3,							// number of elements per vertex
		gl::FLOAT,					// the type of each element
		false,						// take our values as-is
		0,							// next element
		0);							// offset of the first element

	gl::EnableVertexAttribArray(attribute_v_color);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_cube_colors);
	gl::VertexAttribPointer(
		attribute_v_color,			// attribute
		3,							// number of elements per vertex: (r,g,b)
		gl::FLOAT,					// the type of each element
		false,						// take our values as-is
		0,							// next color
		0);							// offset of the first element


	/* рендер куба  */
	int size;
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	gl::GetBufferParameteriv(gl::ELEMENT_ARRAY_BUFFER,
			gl::BUFFER_SIZE, &size);
	gl::DrawElements(gl::TRIANGLES, size/sizeof(GLushort),
			gl::UNSIGNED_SHORT, 0);

	gl::DisableVertexAttribArray(attribute_coord3d);
	gl::DisableVertexAttribArray(attribute_v_color);

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
	glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_x);
	anim *= glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_y);

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
	gl::DeleteBuffers(1, &vbo_cube_colors);
	gl::DeleteBuffers(1, &vbo_cube_vertices);
	gl::DeleteBuffers(1, &ibo_cube_elements);

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

	if (SDL_GL_CreateContext(window) == NULL) {
		cerr << "Error - SDL_GL_CreateContext: " << SDL_GetError();
		return EXIT_FAILURE;
	}

	if (!init_resources()) return EXIT_FAILURE;

	winDisp(window);
	free_resources();
	return EXIT_SUCCESS;
}
