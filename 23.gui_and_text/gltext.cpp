/**
 * From the OpenGL Programming wikibook: http://en.wikibooks.org/wiki/Opengl::Programming
 * This file is in the public domain.
 * Contributors: Guus Sliepen, Sylvain Beucler
 */
#include "gltext.hpp"

int screen_width=800, screen_height=600;

const char *font_filepath = "fonts/FreeSans.ttf";
const char *vshader = "glsl/text.v.glsl";
const char *fshader = "glsl/text.f.glsl";

GLuint program;
GLint attribute_coord;
GLint uniform_tex;
GLint uniform_color;

struct point {
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;
};

GLuint vbo;

bool init_resources() {

	program = create_program(vshader, fshader);
	if(program == 0)
		return false;

	attribute_coord = get_attrib(program, "coord");
	uniform_tex = get_uniform(program, "tex");
	uniform_color = get_uniform(program, "color");

	if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
		return false;

	// Create the vertex buffer object
	gl::GenBuffers(1, &vbo);

	return true;
}

/**
 * Render text using the currently loaded font and currently set font size.
 * Rendering starts at coordinates (x, y), z is always 0.
 * The pixel coordinates that the FreeType2 library uses are scaled by (sx, sy).
 */
void render_text(const char *text, int x, int y) {

	/* Create a texture that will be used to hold one "glyph" */
	GLuint tex;
	gl::ActiveTexture(gl::TEXTURE0);
	gl::GenTextures(1, &tex);
	gl::BindTexture(gl::TEXTURE_2D, tex);
	gl::Uniform1i(uniform_tex, 0);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::EnableVertexAttribArray(attribute_coord);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::VertexAttribPointer(attribute_coord, 4, gl::FLOAT, 0, 0, 0);

  if ( TTF_Init() < 0 ) fprintf(stderr, "Couldn't initialize TTF");
  TTF_Font *font = TTF_OpenFont(font_filepath, 24);
  if(!font) SDL_Log("Couldn't make TTF font object");

	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
  SDL_Color c = { 0, 0, 0, 255 };
	SDL_Surface *img = TTF_RenderUTF8_Blended(font, text, c);
  TTF_CloseFont(font);

	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::ALPHA, img->w, img->h, 0,
			gl::RGBA, gl::UNSIGNED_BYTE, img->pixels);

	/* Calculate the vertex and texture coordinates */
	float sx = 2.0 / screen_width;
	float sy = 2.0 / screen_height;

	float fw = img->w * sx;
	float fh = img->h * sy;

	float fx = -1.0 + x * sx;
	float fy =  1.0 - y * sy;

	point box[4] = {
		{fx, fy, 0, 0},
		{fx + fw, fy, 1, 0},
		{fx, fy - fh, 0, 1},
		{fx + fw, fy - fh, 1, 1},
	};

	/* Draw the text on the screen */
	gl::BufferData(gl::ARRAY_BUFFER, sizeof box, box, gl::DYNAMIC_DRAW);
	gl::DrawArrays(gl::TRIANGLE_STRIP, 0, 4);
	gl::DisableVertexAttribArray(attribute_coord);

	SDL_FreeSurface(img);
	gl::DeleteTextures(1, &tex);
}

void render(SDL_Window* window) {

	/* White background */
	gl::ClearColor(1, 1, 1, 1);
	gl::Clear(gl::COLOR_BUFFER_BIT);
	gl::Enable(gl::BLEND);
	gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);

	GLfloat color[4] = { 0.2, 0.2, 0.4, 0.9 };

	gl::UseProgram(program);
	gl::Uniform4fv(uniform_color, 1, color);
	render_text("Тестовый текст", 12, 0);

	SDL_GL_SwapWindow(window);
}

void onResize(int width, int height) {
	screen_width = width;
	screen_height = height;
	gl::Viewport(0, 0, screen_width, screen_height);

}

void free_resources() {
	gl::DeleteProgram(program);
}

void mainLoop(SDL_Window* window) {
	while (true) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				return;
			if (ev.type == SDL_WINDOWEVENT &&
					ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				onResize(ev.window.data1, ev.window.data2);
		}
		render(window);
	}
}

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Basic Text",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screen_width, screen_height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window == NULL) {
		std::cerr << "Error: can't create window: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	if (SDL_GL_CreateContext(window) == NULL) {
		std::cerr << "Error: SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	if(!gl::sys::LoadFunctions())
	{
		std::cerr << "Can't load OpenGl finctions" << std::endl;
		return EXIT_FAILURE;
	}


	if (!init_resources())
		return EXIT_FAILURE;

    mainLoop(window);

	free_resources();
	return EXIT_SUCCESS;
}
