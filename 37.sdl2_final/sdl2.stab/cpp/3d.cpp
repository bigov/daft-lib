/**
 * Формирование графического контента
 */

#include "../hpp/swop.hpp"

namespace app {

Content3D::Content3D(): win_aspect(1.0), err("")
{}

bool Content3D::init(Conf_Content * shaders)
{
	cfg = shaders;
	try {
		prog = new GLSLProgram();
		prog->addShader(cfg->vshader_pname->c_str());
		prog->addShader(cfg->fshader_pname->c_str());
		prog->use();
	}	catch(errGLSL & e)
	{
		err = e.what();
		return false;
	}
	
	set_vertices();
	set_texcoords();

	try { prog->addTexture(cfg->texture_pname->c_str()); }
	catch(errGLSL & e)
	{
		err = e.what(); 
		return false;
	}
	
	set_draw_order();
	
	gl::Enable(gl::BLEND);
	gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
	gl::ClearColor(0.5, 0.69, 1.0, 1.0);
	gl::Enable(gl::DEPTH_TEST);
	gl::DepthFunc(gl::LESS);

	return true;
}

Content3D::~Content3D(void)
{
	free_resources();
}

void Content3D::resize_viewport(int w, int h)
{
	if(h == 0) win_aspect = 1.0;
	else win_aspect = (float)w/(float)h;
	gl::Viewport(0, 0, w, h);
	return;
}

void Content3D::push_params(ParamsWindow p)
{	
	switch(p.ev)
	{
		case RESIZE:
			resize_viewport(p.w, p.h);
			break;
		default:
			break;
	}
	render_content();
	return;
}

void Content3D::push_moving(Moving m)
{
	mov = m;
	render_content();
	return;
}

void Content3D::set_vertices(void)
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
	try{ prog->setAttrib("coord3d", 3, cube_vertices, 3*4*6);}
	catch(errGLSL & e) { SDL_Log(e.what().c_str());	}

	return;
}

// порядок обхода элеменов массива 3d координат вершин куба
// для построения (треугольниками) сторон куба
void Content3D::set_draw_order(void)
{
	GLuint cube_elements[] = {
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
	try {prog->setBufferIndex(cube_elements, 35);}
	catch(errGLSL & e) { SDL_Log(e.what().c_str());	}

	return;
}

void Content3D::set_texcoords(void)
{
	GLfloat cube_texcoords[2*4*6] = {
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0 
	};
	try {	prog->setAttrib("texcoord", 2, cube_texcoords, 48); }
	catch(errGLSL & e) { SDL_Log(e.what().c_str());	}

	return;
}

/**
 * Constracting scene viewing
 */
void Content3D::make_view()
{

	float speed = 0.1;

	static float x_look_from = 0.0;
	static float x_look_to = 0.0;

	x_look_from += speed * mov.x;
	x_look_to += speed * mov.x;

	static float y_look_from = 2.0;
	static float y_look_to = 0.0;

	y_look_from += speed * mov.y;
	y_look_to += speed * mov.y;

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
		45.0f, win_aspect, 0.1f, 10.0f);
	glm::mat4 mvp = projection * view * model * anim;

	prog->setUniform("mvp", mvp);

	return;
}

/* (render) построение изображения */
void Content3D::render_content()
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	prog->use();
	prog->draw();
	make_view();
	return;
}

void Content3D::free_resources(void)
{
	delete prog;
	/*
	 * TODO - проверить деструктор класса программы на наличие
	gl::DeleteBuffers(1, &vbo_cube_vertices);
	gl::DeleteBuffers(1, &vbo_cube_texcoords);
	gl::DeleteBuffers(1, &ibo_cube_elements);
	gl::DeleteTextures(1, &texture_id);
	*/

	return;
}
//////////////////
} // namespace app

