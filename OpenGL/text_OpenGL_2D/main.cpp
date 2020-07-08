/*
 * OpenGL sample application demonstrating the use of a wrapper
 *
 */
#include <iostream>
#include <vector>
#include <png.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "shaders.hpp"
#include "font/map.hpp"

#include <sstream>
#include <algorithm>
#include <iterator>

#define ERR throw std::runtime_error
#define POINTER(i) reinterpret_cast<const GLvoid*>(i)

static const int position_size = 2;
static const int color_size = 4;
static const int texture_size = 2;
static const unsigned atribs_count = position_size + color_size + texture_size;

struct pngImg
{
  int w = 0;
  int h = 0;
  std::vector<unsigned char> vector = std::vector<unsigned char>(0);
};


std::pair<float, float> convert2opengl(int x, int y, int x_max, int y_max)
{
  float fx = static_cast<float>(x) * (2.f / static_cast<float>(x_max)) - 1.f;
  float fy = static_cast<float>(y_max - y) * (2.f / static_cast<float>(y_max)) - 1.f;
  return {fx, fy};
}


//## Чтение файла в формате PNG
pngImg get_png_img(const std::string & f_n)
{
#if not defined PNG_SIMPLIFIED_READ_SUPPORTED
  fprintf(stderr, "Error: %s\n", "FAILURE: you must update the \"libpng\".");
#endif

  const char * filename = f_n.c_str();
  png_image info;
  memset(&info, 0, sizeof info);
  info.version = PNG_IMAGE_VERSION;
  if (!png_image_begin_read_from_file(&info, filename))
    fprintf(stderr, "Can't read PNG image file");

  info.format = PNG_FORMAT_RGBA;
  pngImg res = {
    static_cast<int>(info.width),
    static_cast<int>(info.height),
    std::vector<unsigned char>(PNG_IMAGE_SIZE(info), '\0')
  };

  if (!png_image_finish_read(&info, NULL, res.vector.data(), 0, NULL ))
  {
    png_image_free(&info);
    fprintf(stderr, "Error: %s\n", info.message);
  }
  return res;
}


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
/// \brief load_texture
///
void load_texture(void)
{
  // Загрузка текстур поверхностей воксов
  glActiveTexture(GL_TEXTURE0);
  GLuint texture_id = 0;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  std::string fname = texture_file;
  pngImg texture_font = get_png_img("../font/" + fname);
  GLint level_of_details = 0;
  GLint frame = 0;

  glTexImage2D(GL_TEXTURE_2D, level_of_details, GL_RED,
               static_cast<GLsizei>(texture_font.w),
               static_cast<GLsizei>(texture_font.h),
               frame, GL_RGBA, GL_UNSIGNED_BYTE, texture_font.vector.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);
}

///
/// \brief string2vector
/// \param Text
/// \return
///
std::vector<std::string> string2vector(const std::string& Text)
{
  std::vector<std::string> result {};
  for(size_t i = 0; i < Text.size();)
  {
    size_t bytes = 1;
    auto c = static_cast<unsigned char>(Text[i]);
    if( c >= 0xD0 ) bytes = 2;
    result.push_back(Text.substr(i, bytes));
    i += bytes;
  }
  return result;
}


///
/// \brief buffer_data_create
/// \param win_w
/// \param win_h
/// \param Text
/// \param size
/// \param left
/// \param top
/// \return
///
std::vector<float> buffer_data_create(int win_w, int win_h, int left, int top, const std::string& Text, int size_x, int size_y = 0)
{
  std::vector<float> vertices { };
  const size_t quad_array_size = atribs_count * 6;
  if(size_y == 0) size_y = size_x;

  int x0 = left;
  int y1 = top;
  int x1 = x0 + size_x;
  int y0 = y1 + size_y;

  float r = 0.1f, g = 0.1f, b = 0.1f, a = 1.f;

  std::vector<std::string> SymbolsUTF8 = string2vector(Text);

  for(const auto& Symbol: SymbolsUTF8)
  {
    auto T = char_location( Symbol );
    auto L0 = convert2opengl(x0, y0, win_w, win_h);
    auto L1 = convert2opengl(x1, y1, win_w, win_h);

    float quad_array[quad_array_size] = {
      L0.first, L0.second, r, g, b, a, T[0], T[1],
      L1.first, L0.second, r, g, b, a, T[2], T[1],
      L1.first, L1.second, r, g, b, a, T[2], T[3],
      L1.first, L1.second, r, g, b, a, T[2], T[3],
      L0.first, L1.second, r, g, b, a, T[0], T[3],
      L0.first, L0.second, r, g, b, a, T[0], T[1]
    };

    vertices.insert(vertices.end(), quad_array, quad_array + quad_array_size);
    x0 += size_x;
    x1 += size_x;
  }

  return vertices;
}

///
/// \brief vertex_buffer_create
///
void vertex_buffer_create(GLuint position_id, GLuint color_id, GLuint texture_id,
                          const std::vector<float>& vertices)
{
  auto buf_size = static_cast<GLsizeiptr> (vertices.size() * sizeof(float));
  auto stride = static_cast<GLsizei>(sizeof(float) * atribs_count);

  GLuint vbo_pos_hdl = 0;
  glGenBuffers(1, &vbo_pos_hdl);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_hdl);
  glBufferData(GL_ARRAY_BUFFER, buf_size , vertices.data(), GL_STATIC_DRAW);

  GLenum type = GL_FLOAT;
  GLboolean normalized = GL_TRUE;

  glVertexAttribPointer(position_id, position_size, type, normalized, stride,
                        POINTER(0));

  glVertexAttribPointer(color_id, color_size, type, normalized, stride,
                        POINTER(sizeof(float) * position_size));

  glVertexAttribPointer(texture_id, texture_size, type, normalized, stride,
                        POINTER(sizeof(float) * (position_size + color_size)));
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

  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (GL_FALSE == status)
  {
    GLint logLen;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen)
    {
      char * log = new char[logLen];
      GLsizei written;
      glGetProgramInfoLog(program, logLen, &written, log);
      fprintf(stderr, "Error: %s\n", log);
      delete [] log;
    }
  }

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
  GLuint texture_location = static_cast<GLuint>( glGetAttribLocation (program, "vTex") );

  //std::vector<float> vertices = buffer_data_create(win_width, win_height, 10, 24, "р", 28);

  std::vector<float> vertices = buffer_data_create(win_width, win_height, 10, 24, "0123456789", 28);
  std::vector<float> v1 = buffer_data_create(win_width, win_height, 40, 60, "АБВГДЕЖЗИКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ", 7);
  vertices.insert(vertices.end(), v1.begin(),v1.end());
  v1 = buffer_data_create(win_width, win_height, 40, 80, "Нормально!", 7, 14);
  vertices.insert(vertices.end(), v1.begin(),v1.end());

  GLsizei count_vertices = static_cast<GLsizei>( vertices.size() / atribs_count );

  vertex_buffer_create( vpos_location, color_location, texture_location, vertices );
  load_texture();

  glEnableVertexAttribArray(vpos_location);
  glEnableVertexAttribArray(color_location);
  glEnableVertexAttribArray(texture_location);

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
  int window_width = 300;
  int window_height = 200;

  opengl_window_show(window_width, window_height);
  exit(EXIT_SUCCESS);
}

