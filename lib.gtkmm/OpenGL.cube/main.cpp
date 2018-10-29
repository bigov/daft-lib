/* Filename: main.cpp
 *
 */
#include "glarea.hpp"
#include "tools.hpp"

glm::mat4 model {1}, view {}, proj {}, MVP {};
GLint uniMVP = 0;

void init_buffers(void)
{
  glm::vec3 toUp(0.f, 1.f, 0.f);

  GLuint vbo;
  glGenBuffers(1, &vbo);

  GLfloat points[] = {
    // Coordinates        Color
      0.f, 0.f, 0.f,      1.0f, 1.0f, 0.0f,
  };
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  // Create VAO
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Specify layout of point data
  GLuint posAttrib = get_attrib_location("pos");

  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
    6 * sizeof(GLfloat), 0);

  // Set up transformation matrices
  uniMVP = get_uniform_location("MVP");

  view = glm::lookAt(glm::vec3(0.0f, 0.4f, 1.3f),
        glm::vec3(0.0f, 0.0f, 0.0f), toUp),
  proj = glm::perspective(glm::radians(45.0f), 8.0f / 6.0f, 0.1f, 10.0f),

  glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
  glDisable(GL_CULL_FACE);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  return;
}

///----------------------------------------------------------------------------
///
bool render_gl_content(const Glib::RefPtr<Gdk::GLContext>&)
{
  model *= glm::rotate(0.065f, glm::vec3(1,1,0));
  MVP = proj * view * model;
  glUniformMatrix4fv(uniMVP, 1, GL_FALSE, glm::value_ptr(MVP));

  // Render frame
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDrawArrays(GL_POINTS, 0, 1);
  return true;
}

///----------------------------------------------------------------------------
/// \brief main
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  win_gl OpenGLWindow;
  init_program();
  init_buffers();
  return app->run(OpenGLWindow);
}
