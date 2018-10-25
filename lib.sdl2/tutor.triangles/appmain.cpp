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

const char vfname[] = GLSLDIR DS "triangle.v.glsl";
const char ffname[] = GLSLDIR DS "triangle.f.glsl";

int	screen_width = 1024, screen_height = 768;

GLuint program;
GLuint vbo_triangle, vbo_triangle_colors;
GLint attribute_coord3d, attribute_v_color;
GLint uniform_fade, uniform_m_transform;

struct attributes {
	GLfloat coord3d[3];
	GLfloat v_color[3];
};

/**
 * Настройка шейдерных функций модификации изображения
 */
int bind_uniforms(void)
{
	const char* uniform_name;

	/* управление изменением прозрачности */
	uniform_name = "fade";
	uniform_fade = gl::GetUniformLocation(program, uniform_name);
	if (uniform_fade == -1) {
		cerr << "Can't bind uniform_fade " << uniform_name << endl;
		return false;
	}

	/* изменение положения вершин */
	uniform_name = "m_transform";
	uniform_m_transform = gl::GetUniformLocation(program, uniform_name);
	if (uniform_m_transform == -1) {
		cerr << "Could not bind uniform_fade " << uniform_name << endl;
		return false;
	}
	return true;
}

/* Создание и компиляция шейдерной программы*/
bool init_resources(void)
{
	GLint link_ok = false;

	//  Загрузка расширений OpenGL для работы с GLSL
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
	if(!didLoad) {
		cerr << "ERROR: loading OGL functions.\n" <<
			"Number of functions that failed to load: "
			<< didLoad.GetNumMissing() << endl;
		return false;
	}

	struct attributes triangle_attributes[] = {
		{{ 0.0,  0.8, 0.0}, {1.0, 1.0, 0.0}},
		{{-0.8, -0.8, 0.0}, {0.0, 0.0, 1.0}},
		{{ 0.8, -0.8, 0.0}, {1.0, 0.0, 0.0}},
	};

	gl::GenBuffers(1, &vbo_triangle);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_triangle);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(triangle_attributes),
		triangle_attributes, gl::STATIC_DRAW);

	// загрузка и компиляция шейдеров
	GLuint vs, fs; /* при ошибке возвращается 0 (false) */
	if (!(vs = create_shader(vfname, gl::VERTEX_SHADER))) return false;
	if (!(fs = create_shader(ffname, gl::FRAGMENT_SHADER))) return false;

	program = gl::CreateProgram();
	gl::AttachShader(program, vs);
	gl::AttachShader(program, fs);
	gl::LinkProgram(program);
	gl::GetProgramiv(program, gl::LINK_STATUS, &link_ok);
	if (!link_ok) {
		cerr << "Error in gl::LinkProgram." << endl;
		return false;
	}

	const char* attribute_name;
	attribute_name = "coord3d";
	attribute_coord3d = gl::GetAttribLocation(program, attribute_name);
	/* при oшибке возвращается -1 */
	if (attribute_coord3d == -1) {
		fprintf(stderr, "Can't bind attribute \"%s\"\n", attribute_name);
		return false;}
	attribute_name = "v_color";
	attribute_v_color = gl::GetAttribLocation(program, attribute_name);
	if (attribute_v_color == -1) {
		fprintf(stderr, "Can't not bind attribute \"%s\"\n", attribute_name);
	return false;
	}

	/*  привязка функций управления положением вершин и прозрачностью */
	return bind_uniforms();
}

/* (render) построение изображения */
void onDisplay(SDL_Window * window)
{
	gl::Clear(gl::COLOR_BUFFER_BIT);
	gl::EnableVertexAttribArray(attribute_coord3d);
	gl::EnableVertexAttribArray(attribute_v_color);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_triangle);
	gl::UseProgram(program);

	gl::VertexAttribPointer(
		attribute_coord3d,			// attribute
		3,							// number of elements per vertex
		gl::FLOAT,					// the type of each element
		false,						// take our values as-is
		sizeof(5*glshort),  // next element
		0							// offset of the first element
	);
	gl::VertexAttribPointer(
		attribute_v_color,			// attribute
		3,							// number of elements per vertex: (r,g,b)
		gl::FLOAT,					// the type of each element
		false,						// take our values as-is
		sizeof(struct attributes),  // next color
		(GLvoid*) offsetof(struct attributes, v_color));

	gl::DrawArrays(gl::TRIANGLES, 0, 3);
	gl::DisableVertexAttribArray(attribute_coord3d);
	gl::DisableVertexAttribArray(attribute_v_color);
	SDL_GL_SwapWindow(window);
	return;
}

/**
 * Функции динамического изменения шейдеров
 */
void logic(void)
{
	float move = sinf(SDL_GetTicks() / 1000.0);
	float angle = SDL_GetTicks() / 1000.0 * 45;
	float cur_fade = sinf(SDL_GetTicks() / 1000.0) / 2 + 0.5;

	glm::vec3 axis_z(0, 0, 1);
	glm::mat4 m_transform =
		glm::translate(glm::mat4(1.0f), glm::vec3(move, 0.0, 0.0)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_z);

	/* управление положением в пространстве */
	gl::UniformMatrix4fv(uniform_m_transform, 1, false,
			glm::value_ptr(m_transform));

	/* управление прозрачностью */
	gl::Uniform1f(uniform_fade, cur_fade);
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

	SDL_Event ev;
	SDL_PollEvent(&ev);
	while ( SDL_QUIT != ev.type ) {
		logic();
		onDisplay(window);
		SDL_PollEvent(&ev);
	}
	return;
}

void free_resources(void)
{
	gl::DeleteProgram(program);
	gl::DeleteBuffers(1, &vbo_triangle);
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

	bool init_success = init_resources();
	if (!init_success) return EXIT_FAILURE;

	winDisp(window);
	free_resources();
	return EXIT_SUCCESS;
}
