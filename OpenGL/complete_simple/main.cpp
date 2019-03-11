/* Intel: создает окно по 4.2-core включительно; профиль compatibility c Intel не создается ни с одной из весий. */

#include <iostream>
#include <thread>
#include <sys/stat.h>
#include <fstream>

#include "glad.h"
#include <GLFW/glfw3.h>

#define ERR throw std::runtime_error

GLuint
  vao_id = 0,
  data_buf = 0,
  index_buf = 0,
  attr_position = 0,
  attr_color = 0,
  program = 0;

//## File read
std::unique_ptr<char[]> read_file(const std::string &FNname)
{
  // проверка наличия файла
  struct stat Buf;
  if (stat (FNname.c_str(), &Buf) != 0) ERR("Missing file: " + FNname);
  // чтение файла
  std::ifstream file(FNname, std::ios::in|std::ios::ate);
  file.exceptions(std::ios_base::badbit|std::ios_base::failbit);
  if (!file.is_open()) ERR("Can't open " + FNname);

  auto size = file.tellg();
  if(size < 1) return nullptr;
  auto data_size = static_cast<size_t>(size) + 1;
  auto data = std::make_unique<char[]>(data_size);

  file.seekg(0, std::ios::beg);
  file.read(data.get(), size);
  file.close();

  data[data_size - 1] = '\0';
  return data;
}

//## GLFW
void key_callback(GLFWwindow* window, int, int, int, int)
{
  glfwSetWindowShouldClose(window, GLFW_TRUE);
}

//## GLFW
void error_callback(int error, const char* description)
{
  ERR("GLFW error " + std::to_string(error) + ": " + description);
}

//## GLFW
GLFWwindow* glfw_win(void)
{
  glfwSetErrorCallback(error_callback);
  if(!glfwInit()) ERR("Error init GLFW lib.");
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  auto win_ptr = glfwCreateWindow(640, 480, "test", nullptr, nullptr);
  if (nullptr == win_ptr) ERR("Creating Window fail\n");
  glfwSetKeyCallback(win_ptr, key_callback);
  glfwMakeContextCurrent(win_ptr);
  glfwSwapInterval(0);
  if(!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) ERR("FAILURE: can't load GLAD.");
  return win_ptr;
}

//## OpenGL
void compile_shader(GLuint shader)
{
  glCompileShader(shader);
  GLint result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if(GL_FALSE == result)
  {
    GLint logLen;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
    if(logLen > 0)
    {
      auto log_size = static_cast<unsigned>(logLen);
      auto log = std::make_unique<char[]>(log_size + 1);
      GLsizei written;
      glGetShaderInfoLog(shader, logLen, &written, log.get());
      log[log_size] = '\0';
      std::cout << "\n" << log.get() << '\n';
    }
    ERR("Error compiling SHADER\n");
  }
  return;
}

//## OpenGL
void create_program(void)
{
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  if (!vertShader) ERR("Error create GL_VERTEX_SHADER");

  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  if (!fragShader) ERR("Error create GL_FRAGMENT_SHADER");

  auto Buff = read_file("vert.glsl");
  auto b = Buff.get();
  glShaderSource(vertShader, 1, &b, nullptr);
  compile_shader(vertShader);

  Buff = read_file("frag.glsl");
  b = Buff.get();
  glShaderSource(fragShader, 1, &b, nullptr);
  compile_shader(fragShader);

  program = glCreateProgram();
  if (!program) ERR("Error creating GLSL program\n");
  glAttachShader(program, vertShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (GL_FALSE == status)
  {
    GLint logLen;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 0)
    {
      auto log_size = static_cast<size_t>(logLen);
      auto log = std::make_unique<char[]>(log_size + 1);
      GLsizei written;
      glGetProgramInfoLog(program, logLen, &written, log.get());
      log[log_size] = '\0';
      std::cout << log.get() << '\n';
    }
    ERR("Failed to link GLSL program.\n");
  }
  glUseProgram(program);
  attr_position = glGetAttribLocation(program, "VertexPosition");
  attr_color = glGetAttribLocation(program, "VertexColor");
  glUseProgram(0);
}

//## ---
void init_scene(void)
{                           //  x      y     z     r     g     b
  float pos_and_color[18] = { -0.8f, -0.8f, 0.0f, 0.4f, 1.0f, 0.4f,
                               0.8f, -0.8f, 0.0f, 1.0f, 0.4f, 0.4f,
                               0.0f,  0.8f, 0.0f, 1.0f, 1.0f, 0.4f };
  GLsizei stride = 6 * sizeof(GLfloat);
  GLsizei data_size = 3 * stride;

  glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);

  glGenBuffers(1, &data_buf);
  glBindBuffer(GL_ARRAY_BUFFER, data_buf);
  glBufferData(GL_ARRAY_BUFFER, data_size, pos_and_color, GL_STATIC_DRAW);
  glVertexAttribPointer(attr_position, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0*sizeof(GLfloat)));
  glVertexAttribPointer(attr_color, 3, GL_FLOAT, GL_TRUE, stride, reinterpret_cast<void*>(3*sizeof(GLfloat)));
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &index_buf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf);
  GLuint idx[3] = {0, 1, 2};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(float), idx, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
  return;
}

//## ---
void show(GLFWwindow* win_ptr)
{
  create_program();
  init_scene();

  std::chrono::milliseconds pause { 20 };
  while (!glfwWindowShouldClose(win_ptr))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, data_buf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf);
    glEnableVertexAttribArray(attr_position);
    glEnableVertexAttribArray(attr_color);

    glUseProgram(program);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    //glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr, 0);

    glDisableVertexAttribArray(attr_color);
    glDisableVertexAttribArray(attr_position);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(win_ptr);
    glfwPollEvents();
    std::this_thread::sleep_for(pause);
  }
  glfwDestroyWindow(win_ptr);
  glfwTerminate();
}

//## ---
int main(int, char**)
{
  try {
    show(glfw_win());
  } catch(std::exception & e) {
    std::cout << e.what() << "\n";
    return EXIT_FAILURE;
  } catch(...) {
    std::cout << "FAILURE: undefined exception.\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
