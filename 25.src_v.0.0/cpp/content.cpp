/**
 * Формирование графического контента
 */

#include "rigs.hpp"

namespace app {

GLuint vbo_cube_vertices, ibo_cube_elements;
GLuint texture_id, vbo_cube_texcoords;
Prog *prog = NULL;

GLint attribute_coord3d, attribute_texcoord;
GLint uniform_mvp;

void rotate_object(float window_aspect);

// Ввод в графический буфер точек координат вершин фигуры (куба)
//
void set_vertices(GLuint *vbo_vertices)
{

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
	gl::GenBuffers(1, vbo_vertices);
	gl::BindBuffer(gl::ARRAY_BUFFER, *vbo_vertices);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(cube_vertices),
			cube_vertices, gl::STATIC_DRAW);
	return;
}

/**
 * Ввод в графический буфер сторон (из треугольников) 3d куба
 */
void bind_elements(GLuint *ibo_elements)
{
	// порядок обхода элеменов массива 3d координат вершин куба
	// для построения (треугольниками) сторон куба
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
	gl::GenBuffers(1, ibo_elements);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, *ibo_elements);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(cube_elements),
			cube_elements, gl::STATIC_DRAW);
	return;
}

void set_texcoords(GLuint *vbo_texcoords)
{
	GLfloat cube_texcoords[2*4*6] = {
		// front
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	};
	for (int i = 1; i < 6; i++)
		memcpy(&cube_texcoords[i*4*2],&cube_texcoords[0],2*4*sizeof(GLfloat));

	gl::GenBuffers(1, vbo_texcoords);
	gl::BindBuffer(gl::ARRAY_BUFFER, *vbo_texcoords);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(cube_texcoords),
			cube_texcoords, gl::STATIC_DRAW);

	return;
}

bool bind_texture(GLuint *id, const char *filename)
{
	/* загрузка текстуры */
	SDL_Surface *res_texture = IMG_Load(filename);
	if (!res_texture) {
		SDL_Log("Err texture load: %s", SDL_GetError());
		return false;
	}

	gl::GenTextures(1, id);
	gl::BindTexture(gl::TEXTURE_2D, *id);
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

	return true;
}

void content_create(Config *cfg)
{
	set_vertices(&vbo_cube_vertices);
	bind_elements(&ibo_cube_elements);
	set_texcoords(&vbo_cube_texcoords);

	if(!bind_texture(&texture_id, cfg->texture_pname))
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Can't bind texture");

	std::vector<Shader> shaders	{
		Shader((PathName)cfg->vshader_pname, gl::VERTEX_SHADER),
		Shader((PathName)cfg->fshader_pname, gl::FRAGMENT_SHADER)
	};

	prog = new Prog(shaders);
	attribute_coord3d = prog->attrib("coord3d");
	attribute_texcoord = prog->attrib("texcoord");
	uniform_mvp = prog->uniform("mvp");

	gl::Enable(gl::BLEND);
	gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
	gl::ClearColor(0.5, 0.69, 1.0, 1.0);
	gl::Enable(gl::DEPTH_TEST);
	gl::DepthFunc(gl::LESS);

	return;
}

/**
 * Constracting scene viewing
 */
void make_view(float window_aspect, Rods gait)
{

	float y_speed = 0.1;
	static float y_look_from = 2.0;
	static float y_look_to = 0.0;

	if(gait.up) {
		y_look_from += y_speed;
		y_look_to += y_speed;
	}

	if(gait.down) {
		y_look_from -= y_speed;
		y_look_to -= y_speed;
	}

	glm::vec3 axis_x(1, 0, 0);
	glm::vec3 axis_y(0, 1, 0);

	float angle = SDL_GetTicks() / 1000.0 * 15.0; // 15 градусов/секунду

	glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_y);
	// anim *= glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_x);

	glm::mat4 model = glm::translate(glm::mat4(1.0f),
		glm::vec3(0.0, 0.0, -4.0));

	glm::mat4 view = glm::lookAt(glm::vec3(0.0, y_look_from, 0.0),
		glm::vec3(0.0, 0.0 + y_look_to, -4.0), glm::vec3(0.0, 1.0, 0.0));

	glm::mat4 projection = glm::perspective(
		45.0f, window_aspect, 0.1f, 10.0f);
	glm::mat4 mvp = projection * view * model * anim;

	gl::UniformMatrix4fv(uniform_mvp, 1, false, glm::value_ptr(mvp));
	return;
}

/* (render) построение изображения */
void render_content(float window_aspect, Rods gait)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

  // show 2D text label
	//show_text("TST FPS", 1024, 768);

	prog->use();

	gl::EnableVertexAttribArray(attribute_coord3d);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_cube_vertices);
	gl::VertexAttribPointer(
		attribute_coord3d,  // attribute
		3,				          // number of elements per vertex
		gl::FLOAT,		      // the type of each element
		false,			        // take our values as-is
		0,				          // next element
		0				            // offset of the first element
	);
	gl::EnableVertexAttribArray(attribute_texcoord);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo_cube_texcoords);
	gl::VertexAttribPointer(
		attribute_texcoord, // attribute
		2,                  // number of elements per vertex, here (x,y)
		gl::FLOAT,          // the type of each element
		false,				      // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
	);

	int size = 0; // размер массива элементов
	gl::GetBufferParameteriv(gl::ELEMENT_ARRAY_BUFFER, gl::BUFFER_SIZE, &size);
	gl::DrawElements(gl::TRIANGLES, size/sizeof(GLushort),gl::UNSIGNED_SHORT,0);

	gl::DisableVertexAttribArray(attribute_coord3d);
	gl::DisableVertexAttribArray(attribute_texcoord);

	make_view(window_aspect, gait);

	//unbind VAO & program
	gl::BindVertexArray(0);
	prog->stopUsing();

	return;
}

void free_resources(void)
{
	gl::DeleteProgram(prog->id());
	delete prog;
	gl::DeleteBuffers(1, &vbo_cube_vertices);
	gl::DeleteBuffers(1, &vbo_cube_texcoords);
	gl::DeleteBuffers(1, &ibo_cube_elements);
	gl::DeleteTextures(1, &texture_id);
	return;
}
//////////////////
} // namespace app

