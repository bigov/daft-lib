/**
 * This file is in the public domain.
 * Contributors: Sylvain Beucler
 */
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gl_core_3_0.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_utils.hpp"

using namespace std;

int screen_width=800, screen_height=600;
GLuint program;
GLuint normalmap_id;
GLuint sphere_vbo = -1;
GLint attribute_v_coord = -1, attribute_v_normal = -1, attribute_v_texcoords = -1, attribute_v_tangent = 1;
GLint uniform_m = -1, uniform_v = -1, uniform_p = -1,
    uniform_m_3x3_inv_transp = -1, uniform_v_inv = -1,
    uniform_normalmap = -1;

struct demo {
    const char* texture_filename;
    const char* vshader_filename;
    const char* fshader_filename;
};
struct demo demos[] = {
    // Lighting of Bumpy Surfaces
    { "normals.png", "cube.v.glsl", "cube.f.glsl" },
};
int cur_demo = 0;

class Mesh {
private:
  GLuint vbo_vertices, vbo_normals, vbo_texcoords, vbo_tangents, ibo_elements;
public:
  vector<glm::vec4> vertices;
  vector<glm::vec3> normals;
  vector<glm::vec2> texcoords;
  vector<glm::vec3> tangents;
  vector<GLushort> elements;
  glm::mat4 object2world;

  Mesh() : vbo_vertices(0), vbo_normals(0), vbo_texcoords(0), vbo_tangents(0),
           ibo_elements(0), object2world(glm::mat4(1)) {}
  ~Mesh() {
    if (vbo_vertices != 0)
      gl::DeleteBuffers(1, &vbo_vertices);
    if (vbo_normals != 0)
      gl::DeleteBuffers(1, &vbo_normals);
    if (vbo_texcoords != 0)
      gl::DeleteBuffers(1, &vbo_texcoords);
    if (vbo_tangents != 0)
      gl::DeleteBuffers(1, &vbo_tangents);
    if (ibo_elements != 0)
      gl::DeleteBuffers(1, &ibo_elements);
  }

  /**
   * Express surface tangent in object space
   * http://www.terathon.com/code/tangent.html
   * http://www.3dkingdoms.com/weekly/weekly.php?a=37
   */
  void compute_tangents() {
    tangents.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));

    for (int i = 0; i < elements.size(); i+=3) {
      int i1 = elements.at(i);
      int i2 = elements.at(i+1);
      int i3 = elements.at(i+2);
      glm::vec3 p1(vertices.at(i1));
      glm::vec3 p2(vertices.at(i2));
      glm::vec3 p3(vertices.at(i3));
      glm::vec2 uv1 = texcoords.at(i1);
      glm::vec2 uv2 = texcoords.at(i2);
      glm::vec2 uv3 = texcoords.at(i3);

      glm::vec3 p1p2 = p2 - p1;
      glm::vec3 p1p3 = p3 - p1;
      glm::vec2 uv1uv2 = uv2 - uv1;
      glm::vec2 uv1uv3 = uv3 - uv1;

      float c = uv1uv2.s * uv1uv3.t - uv1uv3.s * uv1uv2.t;
      if (c != 0) {
        float mul = 1.0 / c;
        glm::vec3 tangent = (p1p2 * uv1uv3.t - p1p3 * uv1uv2.t) * mul;
        tangents.at(i1) = tangents.at(i2) = tangents.at(i3) = glm::normalize(tangent);
      }
    }
  }

  /**
   * Store object vertices, normals and/or elements in graphic card
   * buffers
   */
  void upload() {
    if (this->vertices.size() > 0) {
		gl::GenBuffers(1, &this->vbo_vertices);
		gl::BindBuffer(gl::ARRAY_BUFFER, this->vbo_vertices);
		gl::BufferData(gl::ARRAY_BUFFER, this->vertices.size() * sizeof(this->vertices[0]),
		this->vertices.data(), gl::STATIC_DRAW);
    }

    if (this->normals.size() > 0) {
		gl::GenBuffers(1, &this->vbo_normals);
		gl::BindBuffer(gl::ARRAY_BUFFER, this->vbo_normals);
		gl::BufferData(gl::ARRAY_BUFFER, this->normals.size() * sizeof(this->normals[0]),
		this->normals.data(), gl::STATIC_DRAW);
    }

    if (this->texcoords.size() > 0) {
		gl::GenBuffers(1, &this->vbo_texcoords);
		gl::BindBuffer(gl::ARRAY_BUFFER, this->vbo_texcoords);
		gl::BufferData(gl::ARRAY_BUFFER, this->texcoords.size() * sizeof(this->texcoords[0]),
		this->texcoords.data(), gl::STATIC_DRAW);
    }

    if (this->tangents.size() > 0) {
		gl::GenBuffers(1, &this->vbo_tangents);
		gl::BindBuffer(gl::ARRAY_BUFFER, this->vbo_tangents);
		gl::BufferData(gl::ARRAY_BUFFER, this->tangents.size() * sizeof(this->tangents[0]),
		this->tangents.data(), gl::STATIC_DRAW);
    }

    if (this->elements.size() > 0) {
		gl::GenBuffers(1, &this->ibo_elements);
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, this->ibo_elements);
		gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, this->elements.size() * sizeof(this->elements[0]),
		this->elements.data(), gl::STATIC_DRAW);
    }
  }

  /**
   * Draw the object
   */
void draw() {
    if (this->vbo_vertices != 0) {
		gl::EnableVertexAttribArray(attribute_v_coord);
		gl::BindBuffer(gl::ARRAY_BUFFER, this->vbo_vertices);
		gl::VertexAttribPointer(
        attribute_v_coord,  // attribute
        4,                  // number of elements per vertex, here (x,y,z,w)
        gl::FLOAT,           // the type of each element
        false,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
      );
    }

    if (this->vbo_normals != 0) {
		gl::EnableVertexAttribArray(attribute_v_normal);
		gl::BindBuffer(gl::ARRAY_BUFFER, this->vbo_normals);
		gl::VertexAttribPointer(
        attribute_v_normal,  // attribute
        3,                   // number of elements per vertex, here (x,y,z)
        gl::FLOAT,            // the type of each element
        false,            // take our values as-is
        0,                   // no extra data between each position
        0                    // offset of first element
      );
    }

    if (this->vbo_texcoords != 0) {
		gl::EnableVertexAttribArray(attribute_v_texcoords);
		gl::BindBuffer(gl::ARRAY_BUFFER, this->vbo_texcoords);
		gl::VertexAttribPointer(
        attribute_v_texcoords, // attribute
        2,                     // number of elements per vertex, here (x,y)
        gl::FLOAT,              // the type of each element
        false,              // take our values as-is
        0,                     // no extra data between each position
        0                      // offset of first element
      );
    }

    if (this->vbo_tangents != 0) {
		gl::EnableVertexAttribArray(attribute_v_tangent);
		gl::BindBuffer(gl::ARRAY_BUFFER, this->vbo_tangents);
		gl::VertexAttribPointer(
        attribute_v_tangent, // attribute
        3,                   // number of elements per vertex, here (x,y,z)
        gl::FLOAT,            // the type of each element
        false,            // take our values as-is
        0,                   // no extra data between each position
        0                    // offset of first element
		);
    }

    /* Apply object's transformation matrix */
	gl::UniformMatrix4fv(uniform_m, 1, false,
		glm::value_ptr(this->object2world));
    /* Transform normal vectors with transpose of inverse of upper left
       3x3 model matrix (ex-gl_NormalMatrix): */
    glm::mat3 m_3x3_inv_transp = glm::transpose(
		glm::inverse(glm::mat3(this->object2world)));
	gl::UniformMatrix3fv(uniform_m_3x3_inv_transp, 1, false,
		glm::value_ptr(m_3x3_inv_transp));

    /* Push each element in buffer_vertices to the vertex shader */
    if (this->ibo_elements != 0) {
		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, this->ibo_elements);
		int size;
		gl::GetBufferParameteriv(gl::ELEMENT_ARRAY_BUFFER,
				gl::BUFFER_SIZE, &size);
		gl::DrawElements(gl::TRIANGLES, size/sizeof(GLushort),
				gl::UNSIGNED_SHORT, 0);
    } else {
		gl::DrawArrays(gl::TRIANGLES, 0, this->vertices.size());
    }

    if (this->vbo_tangents != 0)
      gl::DisableVertexAttribArray(attribute_v_tangent);
    if (this->vbo_texcoords != 0)
      gl::DisableVertexAttribArray(attribute_v_texcoords);
    if (this->vbo_normals != 0)
      gl::DisableVertexAttribArray(attribute_v_normal);
    if (this->vbo_vertices != 0)
      gl::DisableVertexAttribArray(attribute_v_coord);
  }
};
Mesh cube;

int init_resources()
{
	//  Загрузка расширений OpenGL для работы с GLSL
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
	if(!didLoad) {
		cerr << "ERROR: loading OGL  functions.\n" <<
			"Number of functions that failed to load: "
			<< didLoad.GetNumMissing() << endl;
		return false;
	}

	printf("init_resources: %s, %s, %s.\n",
		demos[cur_demo].texture_filename, demos[cur_demo].vshader_filename,
		demos[cur_demo].fshader_filename);

	/* загрузка библиотеки SDL2_image  */
	printf("init lib.\n");

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		cerr << "IMG_Init: Failed to init required jpg and png support!"
				<< endl;
		cerr << "IMG_Init: " << IMG_GetError() << endl;
		return false;
	}
	gl::GenTextures(1, &normalmap_id);
	gl::BindTexture(gl::TEXTURE_2D, normalmap_id);

	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	SDL_Surface* res_texture = IMG_Load(demos[cur_demo].texture_filename);
	if (!res_texture) {
		cerr << "IMG_Load: " << SDL_GetError() << endl;
		return false;
	}

	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA,	res_texture->w,
		res_texture->h,	0, gl::RGBA, gl::UNSIGNED_BYTE, res_texture->pixels);

	SDL_FreeSurface(res_texture);

	GLint link_ok = false;

	GLuint vs, fs;
	if ((vs = create_shader(demos[cur_demo].vshader_filename,
		gl::VERTEX_SHADER))   == 0) return 0;
	if ((fs = create_shader(demos[cur_demo].fshader_filename,
		gl::FRAGMENT_SHADER)) == 0) return 0;

	program = gl::CreateProgram();
	gl::AttachShader(program, vs);
	gl::AttachShader(program, fs);
	gl::LinkProgram(program);
	gl::GetProgramiv(program, gl::LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		print_log(program);
		return 0;
	}

  const char* attribute_name;
  attribute_name = "v_coord";
  attribute_v_coord = gl::GetAttribLocation(program, attribute_name);
  if (attribute_v_coord == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return 0;
  }
  attribute_name = "v_normal";
  attribute_v_normal = gl::GetAttribLocation(program, attribute_name);
  if (attribute_v_normal == -1) {
    fprintf(stderr, "Warning: Could not bind attribute %s\n", attribute_name);
  }
  attribute_name = "v_texcoords";
  attribute_v_texcoords = gl::GetAttribLocation(program, attribute_name);
  if (attribute_v_texcoords == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return 0;
  }
  attribute_name = "v_tangent";
  attribute_v_tangent = gl::GetAttribLocation(program, attribute_name);
  if (attribute_v_tangent == -1) {
    fprintf(stderr, "Warning: Could not bind attribute %s\n", attribute_name);
  }
  const char* uniform_name;
  uniform_name = "m";
  uniform_m = gl::GetUniformLocation(program, uniform_name);
  if (uniform_m == -1) {
    fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    return 0;
  }
  uniform_name = "v";
  uniform_v = gl::GetUniformLocation(program, uniform_name);
  if (uniform_v == -1) {
    fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    return 0;
  }
  uniform_name = "p";
  uniform_p = gl::GetUniformLocation(program, uniform_name);
  if (uniform_p == -1) {
    fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    return 0;
  }
  uniform_name = "m_3x3_inv_transp";
  uniform_m_3x3_inv_transp = gl::GetUniformLocation(program, uniform_name);
  if (uniform_m_3x3_inv_transp == -1) {
    fprintf(stderr, "Warning: Could not bind uniform %s\n", uniform_name);
  }
  uniform_name = "v_inv";
  uniform_v_inv = gl::GetUniformLocation(program, uniform_name);
  if (uniform_v_inv == -1) {
    fprintf(stderr, "Warning: Could not bind uniform %s\n", uniform_name);
  }
  uniform_name = "normalmap";
  uniform_normalmap = gl::GetUniformLocation(program, uniform_name);
  if (uniform_normalmap == -1) {
    fprintf(stderr, "Warning: Could not bind uniform %s\n", uniform_name);
  }


  // Cube

  // front
  cube.vertices.push_back(glm::vec4(-1.0, -1.0,  1.0,  1.0));
  cube.vertices.push_back(glm::vec4( 1.0, -1.0,  1.0,  1.0));
  cube.vertices.push_back(glm::vec4( 1.0,  1.0,  1.0,  1.0));
  cube.vertices.push_back(glm::vec4(-1.0,  1.0,  1.0,  1.0));
  // top
  cube.vertices.push_back(glm::vec4(-1.0,  1.0,  1.0,  1.0));
  cube.vertices.push_back(glm::vec4( 1.0,  1.0,  1.0,  1.0));
  cube.vertices.push_back(glm::vec4( 1.0,  1.0, -1.0,  1.0));
  cube.vertices.push_back(glm::vec4(-1.0,  1.0, -1.0,  1.0));
  // back
  cube.vertices.push_back(glm::vec4( 1.0, -1.0, -1.0,  1.0));
  cube.vertices.push_back(glm::vec4(-1.0, -1.0, -1.0,  1.0));
  cube.vertices.push_back(glm::vec4(-1.0,  1.0, -1.0,  1.0));
  cube.vertices.push_back(glm::vec4( 1.0,  1.0, -1.0,  1.0));
  // bottom
  cube.vertices.push_back(glm::vec4(-1.0, -1.0, -1.0,  1.0));
  cube.vertices.push_back(glm::vec4( 1.0, -1.0, -1.0,  1.0));
  cube.vertices.push_back(glm::vec4( 1.0, -1.0,  1.0,  1.0));
  cube.vertices.push_back(glm::vec4(-1.0, -1.0,  1.0,  1.0));
  // left
  cube.vertices.push_back(glm::vec4(-1.0, -1.0, -1.0,  1.0));
  cube.vertices.push_back(glm::vec4(-1.0, -1.0,  1.0,  1.0));
  cube.vertices.push_back(glm::vec4(-1.0,  1.0,  1.0,  1.0));
  cube.vertices.push_back(glm::vec4(-1.0,  1.0, -1.0,  1.0));
  // right
  cube.vertices.push_back(glm::vec4( 1.0, -1.0,  1.0,  1.0));
  cube.vertices.push_back(glm::vec4( 1.0, -1.0, -1.0,  1.0));
  cube.vertices.push_back(glm::vec4( 1.0,  1.0, -1.0,  1.0));
  cube.vertices.push_back(glm::vec4( 1.0,  1.0,  1.0,  1.0));

  for (int i = 0; i < 4; i++) { cube.normals.push_back(glm::vec3( 0.0,  0.0,  1.0)); }  // front
  for (int i = 0; i < 4; i++) { cube.normals.push_back(glm::vec3( 0.0,  1.0,  0.0)); }  // top
  for (int i = 0; i < 4; i++) { cube.normals.push_back(glm::vec3( 0.0,  0.0, -1.0)); }  // back
  for (int i = 0; i < 4; i++) { cube.normals.push_back(glm::vec3( 0.0, -1.0,  0.0)); }  // bottom
  for (int i = 0; i < 4; i++) { cube.normals.push_back(glm::vec3(-1.0,  0.0,  0.0)); }  // left
  for (int i = 0; i < 4; i++) { cube.normals.push_back(glm::vec3( 1.0,  0.0,  0.0)); }  // right

  for (int i = 0; i < 6; i++) {
    // front
    cube.texcoords.push_back(glm::vec2(0.0, 0.0));
    cube.texcoords.push_back(glm::vec2(1.0, 0.0));
    cube.texcoords.push_back(glm::vec2(1.0, 1.0));
    cube.texcoords.push_back(glm::vec2(0.0, 1.0));
  }

  // Triangulate
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
  for (int i = 0; i < sizeof(cube_elements)/sizeof(cube_elements[0]); i++)
    cube.elements.push_back(cube_elements[i]);

  cube.compute_tangents();
  cube.upload();

	// glEnable(gl::DEPTH_TEST);
  gl::Enable(gl::CULL_FACE);
	// glAlphaFunc(gl::GREATER, 0.1);
	// glEnable(gl::ALPHA_TEST);
  gl::Enable(gl::BLEND);
  gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
	// glBlendFunc(gl::ONE, gl::ONE_MINUS_SRC_ALPHA);

	return true;
}

void free_resources()
{
	gl::DeleteProgram(program);
	gl::DeleteTextures(1, &normalmap_id);
}

void logic(void) {
  float angle = SDL_GetTicks() / 1000.0 * glm::radians(10.0);  // 10° per second
  glm::mat4 anim = \
    glm::rotate(glm::mat4(1.0f), angle*3.0f, glm::vec3(1, 0, 0)) *  // X axis
    glm::rotate(glm::mat4(1.0f), angle*2.0f, glm::vec3(0, 1, 0)) *  // Y axis
    glm::rotate(glm::mat4(1.0f), angle*4.0f, glm::vec3(0, 0, 1));   // Z axis

  glm::vec3 object_position = glm::vec3(0.0, 0.0, -2.0);
  glm::mat4 model = glm::translate(glm::mat4(1.0f), object_position);
  glm::mat4 view = glm::lookAt(glm::vec3(0.0, 4.0, 0.0), object_position, glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 projection = glm::perspective(45.0f, 1.0f*screen_width/screen_height, 0.1f, 10.0f);

  gl::UseProgram(program);
  cube.object2world = model * anim;

  gl::UniformMatrix4fv(uniform_v, 1, false, glm::value_ptr(view));
  glm::mat4 v_inv = glm::inverse(view);
  gl::UniformMatrix4fv(uniform_v_inv, 1, false, glm::value_ptr(v_inv));

  gl::UniformMatrix4fv(uniform_p, 1, false, glm::value_ptr(projection));

  return;
}

void draw(SDL_Window* window)
{
	gl::ClearColor(1.0, 1.0, 1.0, 1.0);
	gl::Clear(gl::COLOR_BUFFER_BIT|gl::DEPTH_BUFFER_BIT);
	gl::UseProgram(program);
	gl::Uniform1i(uniform_normalmap, /*gl::TEXTURE*/0);
	cube.draw();
	SDL_GL_SwapWindow(window);
	return;
}

void onReshape(int width, int height) {
  screen_width = width;
  screen_height = height;
  gl::Viewport(0, 0, screen_width, screen_height);
  return;
}

void onMouse(int button, int state, int x, int y) {

/*
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      free_resources();
      cur_demo = (cur_demo + 1) % (sizeof(demos)/sizeof(struct demo));
      init_resources();
  }
*/
  return;
}

void appMainLoop(SDL_Window* window)
{
	SDL_Event ev;
	SDL_PollEvent(&ev);
	while ( SDL_QUIT != ev.type ) {
		logic();
		draw(window);
		SDL_PollEvent(&ev);
		if (ev.type == SDL_WINDOWEVENT
			&& ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			onReshape(ev.window.data1, ev.window.data2);
	}
	return;
}

int main(int argc, char* argv[]) {

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

	if (init_resources()) {
		appMainLoop(window);
	}

	free_resources();
	return EXIT_SUCCESS;
}
