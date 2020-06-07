#include <linmath.h>
#include <png.h>

#include "win.hpp"
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
/// \brief opengl_window_show
/// \param texture_data
///
void opengl_window_show(const unsigned char* texture_data, uint32_t win_width, uint32_t win_height)
{
  static const struct
  {
      float x, y, u, v;
  } vertices[4] = {
      {-1.f,-1.f, 0.f, 1.f },
      { 1.f,-1.f, 1.f, 1.f },
      {-1.f, 1.f, 0.f, 0.f },
      { 1.f, 1.f, 1.f, 0.f }
  };
  static const int attr_count = 4;

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

  GLuint hdl_vao;
  GLuint vertex_buffer, vertex_shader, fragment_shader, program;

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(vertex_shader);

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(fragment_shader);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glActiveTexture(GL_TEXTURE0);
  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, win_width, win_height,
           0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  GLint mvp_location  = glGetUniformLocation(program, "MVP");
  GLint vpos_location = glGetAttribLocation (program, "vPos");
  GLint t2d_location  = glGetAttribLocation (program, "texture_2dcoord");

  glGenVertexArrays(1, &hdl_vao);
  glBindVertexArray(hdl_vao);

  glEnableVertexAttribArray(static_cast<GLuint>(vpos_location));
  glVertexAttribPointer(static_cast<GLuint>(vpos_location), 2, GL_FLOAT,
    GL_FALSE, sizeof(float) * attr_count, POINTER(0));

  glEnableVertexAttribArray(static_cast<GLuint>(t2d_location));
  glVertexAttribPointer(static_cast<GLuint>(t2d_location), 2, GL_FLOAT,
    GL_FALSE, sizeof(float) * attr_count, POINTER(sizeof(float) * 2));

  glClearColor(1.f, 1.f, 1.f, 1.f);
  while (!glfwWindowShouldClose(window))
  {
      float ratio;
      int width, height;
      mat4x4 m, p, mvp;

      glfwGetFramebufferSize(window, &width, &height);
      ratio = static_cast<float>(width)/static_cast<float>(height);
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT);

      mat4x4_identity(m);
      //mat4x4_rotate_Z(m, m, static_cast<GLfloat>(glfwGetTime())/2.f);
      mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
      mat4x4_mul(mvp, p, m);

      glUseProgram(program);
      glUniformMatrix4fv(mvp_location, 1, GL_FALSE, mvp[0]);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      glfwSwapBuffers(window);
      glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}


///
/// \brief savePNG
/// \param image
/// \param width
/// \param height
///
void savePNG(uint8_t *image, int32_t width, int32_t height)
{
    // Файл для сохранения картинки
    FILE *f = fopen("output.png", "wb");

    png_structp png_ptr =
        png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

    png_infop info_ptr = png_create_info_struct(png_ptr);

    png_init_io(png_ptr, f);

    // Изображение в формате RGBA по 8 бит на
    // канал и по четыре канала на пиксель
    png_set_IHDR(
        png_ptr,
        info_ptr,
        width,
        height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_BASE,
        PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    // Одна строка в формате RGBA, 4 канала
    std::vector<uint8_t> row(width * 4);

    // Сохраняем PNG построчно
    for (int32_t y = 0; y < height; ++y)
    {
        // Преобразуем нашу строку из одноканальной в формат RGBA
        for (int32_t x = 0; x < width; ++x)
        {
            // Цвет одинаковый для всех пикселей 0x202020
            row[x * 4 + 0] = 0x20;
            row[x * 4 + 1] = 0x20;
            row[x * 4 + 2] = 0x20;
            // Прозрачность берём из исходных данных
            row[x * 4 + 3] = image[y * width + x];
        }

        // Сохраняем строку в PNG
        png_write_row(png_ptr, row.data());
    }

    png_write_end(png_ptr, 0);

    // Закончили работу, освобождаем ресурсы
    fclose(f);
    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    png_destroy_write_struct(&png_ptr, 0);
}
