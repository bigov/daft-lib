/*
 * OpenGL sample application demonstrating the use of a wrapper
 *
 */
#include <iostream>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "shaders.hpp"

#define POINTER(i) reinterpret_cast<const GLvoid*>(i)

///
/// \brief error_callback
/// \param description
///
static void error_callback(int, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}


///
/// \brief key_callback
/// \param window
/// \param key
/// \param action
///
static void key_callback(GLFWwindow* window, int key, int, int action, int)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}


///
/// \brief window_create
/// \param win_width
/// \param win_height
/// \return
///
GLFWwindow* window_create(int win_width, int win_height)
{
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 0);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

  window = glfwCreateWindow(win_width, win_height, "", NULL, NULL);
  if (!window)
  {
      glfwTerminate();
      exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
  if(!gladLoadGL()) { exit(-1); }

  char title[16] = {0};
  sprintf(title, "OpenGL ver. %d.%d", GLVersion.major, GLVersion.minor);
  glfwSetWindowTitle(window, title);
  glfwSwapInterval(1);

  glEnable(GL_BLEND);      // поддержка прозрачности
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(1.f, 1.f, 1.f, 1.f);

  return window;
}


///
/// \brief vertex_buffer_create
///
GLsizei vertex_buffer_create(GLuint position_location, GLuint color_location, float width, float heigh)
{
  float
      x0 = 1.f,
      x1 = width - 1.f,
      y0 = 1.f,
      y1 = heigh - 1.f;

  float a = 0.0f, b = 1.f;

  std::vector<float> vertices { };

  while(y1 > y0 || x1 > x0)
  {
    float arr[] = {
      x0, y0, a, a, a, 1.f,
      x1, y0, a, a, a, 1.f,
      x1, y1, a, a, a, 1.f,
      x1, y1, a, a, a, 1.f,
      x0, y1, a, a, a, 1.f,
      x0, y0, a, a, a, 1.f,
    };
    vertices.insert(vertices.end(), arr, arr + 36);
    x0 += 1.f; x1 -= 1.f; y0 += 1.f; y1 -= 1.f;
    std::swap(a ,b);
  }
  static const int position_attribs_count = 2;
  static const int color_attribs_count = 4;
  unsigned atribs_count = position_attribs_count + color_attribs_count;
  auto buf_size = static_cast<GLsizeiptr> (vertices.size() * sizeof(float));

  GLenum type = GL_FLOAT;
  auto stride = static_cast<GLsizei>(sizeof(float) * atribs_count);

  GLuint vbo_pos_hdl = 0;
  glGenBuffers(1, &vbo_pos_hdl);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_hdl);
  glBufferData(GL_ARRAY_BUFFER, buf_size , vertices.data(), GL_STATIC_DRAW);

  GLuint index = position_location;
  GLint size = position_attribs_count;
  GLboolean normalized = GL_FALSE;
  const void* pointer = POINTER(0);

  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  glEnableVertexAttribArray(index);

  index = color_location;
  size = color_attribs_count;
  normalized = GL_TRUE;
  pointer = POINTER(sizeof(float) * position_attribs_count);

  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  glEnableVertexAttribArray(index);

  return static_cast<GLsizei>( vertices.size() / atribs_count );
}


///
/// \brief program_create
/// \return
///
GLuint program_create()
{
  GLuint vertex_shader, fragment_shader, program;

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(vertex_shader);

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(fragment_shader);

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  glUseProgram(program);

  return program;
}

///
/// \brief opengl_window_show
/// \param texture_data
///
void opengl_window_show(int win_width, int win_height)
{

  auto window = window_create(win_width, win_height);

  GLuint vao_hdl;
  glGenVertexArrays(1, &vao_hdl);
  glBindVertexArray(vao_hdl);

  auto program = program_create();
  GLuint vpos_location = static_cast<GLuint>( glGetAttribLocation (program, "vPos") );
  GLuint color_location = static_cast<GLuint>( glGetAttribLocation (program, "vColor") );
  auto projection = glGetUniformLocation (program, "projection");

  auto count_vertices = vertex_buffer_create( vpos_location, color_location,
                                              static_cast<float>(win_width), static_cast<float>(win_height));

  float L = 0;
  float R = static_cast<float>(win_width);
  float T = 0;
  float B = static_cast<float>(win_height);

  float ortho_projection[4][4] =
  {
      { 2.0f/(R-L),   0.0f,         0.0f,   0.0f },
      { 0.0f,         2.0f/(T-B),   0.0f,   0.0f },
      { 0.0f,         0.0f,        -1.0f,   0.0f },
      { (R+L)/(L-R),  (T+B)/(B-T),  0.0f,   1.0f },
  };
  glUniformMatrix4fv( projection, 1, 0, ortho_projection[0]);


  while (!glfwWindowShouldClose(window))
  {
      int width, height;

      glfwGetFramebufferSize(window, &width, &height);
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT);
      glDrawArrays(GL_TRIANGLES, 0, count_vertices);
      glfwSwapBuffers(window);
      glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}

///
/// \brief main
/// \return
///
int main(int, char**)
{
  int window_width = 301;
  int window_height = 201;

  opengl_window_show(window_width, window_height);
  exit(EXIT_SUCCESS);
}

