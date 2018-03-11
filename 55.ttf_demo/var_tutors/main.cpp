#include "shader_utils.hpp"

GLuint program;
GLint attribute_coord;
GLint uniform_tex;
GLint uniform_color;

GLFWwindow* window;
int width = 800, height = 600;

struct point {
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;
};

GLuint vbo;
GLuint tex;

FT_Library ft;
FT_Face face;

const char *fontfilename;

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	getchar();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	return;
}

static void mouse_callback(GLFWwindow* window, int button, int action, int mod)
{
	//renderer.mouseButtonCallback(button, action);
	return;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	return;
}

void free_resources() {
	glDeleteProgram(program);
}

int init_resources()
{
	if (FT_Init_FreeType(&ft))
	{
		fprintf(stderr, "Could not init freetype library\n");
		return 0;
	}

	if (FT_New_Face(ft, fontfilename, 0, &face))
	{
		fprintf(stderr, "Could not open font %s\n", fontfilename);
		return 0;
	}

	program = create_program("text.v.glsl", "text.f.glsl");
	if(program == 0) return 0;
	glUseProgram(program);

	attribute_coord = get_attrib(program, "coord");
	uniform_tex = get_uniform(program, "tex");
	uniform_color = get_uniform(program, "color");

	if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1)
		return 0;

	/* Create a texture that will be used to hold one "glyph" */
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(uniform_tex, 0);

	/* We require 1 byte alignment when uploading texture data */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Set up the VBO for our vertex data */
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribute_coord);

	return 1;
}

/**
 * Render text using the currently loaded font and currently set font size.
 * Rendering starts at coordinates (x, y), z is always 0.
 * The pixel coordinates that the FreeType2 library uses are scaled by (sx, sy).
 */
void render_text(const char *text, float x, float y, float sx, float sy) {
	const char *p;
	FT_GlyphSlot g = face->glyph;

	/* Loop through all characters */
	for (p = text; *p; p++) {
		/* Try to load and render the character */
		if (!FT_Load_Char(face, *p, FT_LOAD_RENDER)) std::cout << "err FT_Load_Char\n";

		/* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

		/* Calculate the vertex and texture coordinates */
		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		point box[4] = {
			{x2, -y2, 0, 0},
			{x2 + w, -y2, 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};

		/* Draw the character on the screen */
		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		/* Advance the cursor to the start of the next character */
		x += (g->advance.x >> 6) * sx;
		y += (g->advance.y >> 6) * sy;
	}

	glDisableVertexAttribArray(attribute_coord);
	glDeleteTextures(1, &tex);
}

void display() {
	glfwGetWindowSize(window, &width, &height);
	float sx = 2.0 / width;
	float sy = 2.0 / height;

	GLfloat red[4] = { 1, 0, 0, 1 };
	
	FT_Set_Pixel_Sizes(face, 0, 24);
	glUniform4fv(uniform_color, 1, red);

	render_text("T", 10, 10, sx, sy);
}

int main(int argc, char *argv[])
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window = glfwCreateWindow(width, height, "TTF demo", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	if(!ogl_LoadFunctions()) fprintf(stderr, "Can't load OpenGl finctions");
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(0);

	if (argc > 1)
		fontfilename = argv[1];
	else
		fontfilename = "FreeSans.ttf";

	if (!init_resources())
	{
		fprintf(stderr, "Failed to init.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	display();
	glfwSwapBuffers(window);
	
	while (!glfwWindowShouldClose(window))
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//display();
		//glfwSwapBuffers(window);
		glfwPollEvents();
	}

	free_resources();
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

