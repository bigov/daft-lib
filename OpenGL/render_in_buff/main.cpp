/* Intel: создает окно по 4.2-core включительно; профиль compatibility c Intel не создается ни с одной из весий. */

#include <iostream>
#include <thread>
#include <sys/stat.h>
#include <fstream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define ERR throw std::runtime_error

static int win_w = 640, win_h = 480;

static GLuint
  frame_buff_id = 0,
  vao_main = 0,
  vao_frame = 0,
  main_program = 0,
  frame_program = 0,
  attr_main_position = 0,
  attr_main_color = 0,
  attr_buff_position = 0,
  attr_buff_texcoord = 0,
  buff_texture = 0;         // текстура рендера пространства

static GLint attr_buff_texture = 0;


static std::string
  main_vert_glsl {"glsl/main_vert.glsl"},
  main_frag_glsl {"glsl/main_frag.glsl"},
  buff_vert_glsl {"glsl/buff_vert.glsl"},
  buff_frag_glsl {"glsl/buff_frag.glsl"};

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
void key_callback (GLFWwindow* window, int, int, int, int)
{
  glfwSetWindowShouldClose(window, GLFW_TRUE);
}

//## GLFW
void error_callback [[ noreturn ]] (int error, const char* description)
{
  ERR("GLFW ERROR[" + std::to_string(error) + "] " + description);
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

  auto win_ptr = glfwCreateWindow(win_w, win_h, "test", nullptr, nullptr);
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


//##
GLuint gl_get_attrib(GLuint program, const std::string& attrib_name)
{
  GLint n = glGetAttribLocation(program, attrib_name.c_str());
  if (n < 0) ERR ("ERROR: Not found GLSL attribute " + attrib_name);
  return static_cast<GLuint>(n);
}


//##
GLint gl_get_uniform(GLuint program, const std::string& name )
{
  GLint l = glGetUniformLocation(program, name.c_str());
  if(l < 0) ERR ("ERROR: Not found uniform name: " + name);
  return l;
}


//## OpenGL
GLuint create_program(const std::string& vert_shader, const std::string& frag_shader)
{
  GLuint program = 0;
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  if (!vertShader) ERR("Error create GL_VERTEX_SHADER");

  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  if (!fragShader) ERR("Error create GL_FRAGMENT_SHADER");

  auto Buff = read_file(vert_shader);
  auto b = Buff.get();
  glShaderSource(vertShader, 1, &b, nullptr);
  compile_shader(vertShader);

  Buff = read_file(frag_shader);
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
  return program;
}


//##
void init_pogram_main()
{
  main_program = create_program(main_vert_glsl, main_frag_glsl);
  glUseProgram(main_program);
  attr_main_position = gl_get_attrib(main_program, "VertexPosition");
  attr_main_color = gl_get_attrib(main_program, "VertexColor");
  glUseProgram(0);
}


//##
void init_pogram_buff()
{
  frame_program = create_program(buff_vert_glsl, buff_frag_glsl);
  glUseProgram(frame_program);
  attr_buff_position = gl_get_attrib(frame_program, "VertexPosition");
  attr_buff_texcoord = gl_get_attrib(frame_program, "TextureCoord");
  attr_buff_texture = gl_get_uniform(frame_program, "texFramebuffer");
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

  glGenVertexArrays(1, &vao_main);
  glBindVertexArray(vao_main);

  //data buffer
  GLuint _vbo = 0;
  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, data_size, pos_and_color, GL_STATIC_DRAW);
  glEnableVertexAttribArray(attr_main_position);
  glEnableVertexAttribArray(attr_main_color);
  glVertexAttribPointer(attr_main_position, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0*sizeof(GLfloat)));
  glVertexAttribPointer(attr_main_color, 3, GL_FLOAT, GL_TRUE, stride, reinterpret_cast<void*>(3*sizeof(GLfloat)));
  return;
}

//##
bool init_framebuffer(GLsizei w, GLsizei h)
{
  GLint lod = 0, frame = 0;
  GLfloat Position[8] = {-1.f,-1.f, 1.f,-1.f,-1.f, 1.f, 1.f, 1.f }; // 2D коорд. фрейма
  GLfloat Texcoord[8] = { 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f }; // UV координаты

  glGenVertexArrays(1, &vao_frame);
  glBindVertexArray(vao_frame);

  // Буфер координат вершин фрейма, заполняющего окно приложения
  GLuint vbo_buff_pos = 0;
  glGenBuffers(1, &vbo_buff_pos);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_buff_pos);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Position), Position, GL_STATIC_DRAW);
  glEnableVertexAttribArray(attr_buff_position);
  glVertexAttribPointer(attr_buff_position, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

  // Назначить номер текстуры для использования во фрейм-буфере
  glActiveTexture(GL_TEXTURE0);      // default = GL_TEXTURE0
  glUseProgram(frame_program);
  glUniform1i(attr_buff_texture, 0); // GL_TEXTURE1 == 1
  glUseProgram(0);

  // Буфер UV координат текстуры, в которую рендерится сцена
  GLuint vbo_buff_tex = 0;
  glGenBuffers(1, &vbo_buff_tex);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_buff_tex);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Texcoord), Texcoord, GL_STATIC_DRAW);
  glEnableVertexAttribArray(attr_buff_texcoord);
  glVertexAttribPointer(attr_buff_texcoord, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

  // Память под текстуру, в которую рендерится основная сцена
  glGenTextures(1, &buff_texture);
  glBindTexture(GL_TEXTURE_2D, buff_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, lod, GL_RGBA, w, h, frame, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  glGenFramebuffers(1, &frame_buff_id);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buff_id);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buff_texture, 0);

  GLenum b[1] = { GL_COLOR_ATTACHMENT0 }; //, GL_COLOR_ATTACHMENT1 };
  glDrawBuffers(1, b);

  GLuint rbuf = 0;
  glGenRenderbuffers(1, &rbuf);
  glBindRenderbuffer(GL_RENDERBUFFER, rbuf);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbuf);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);

  return glGetError() == GL_NO_ERROR;
}

//## ---
void show(GLFWwindow* win_ptr)
{
  glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
  glDisable(GL_DEPTH_TEST);

  init_pogram_main();
  init_pogram_buff();
  init_scene();
  init_framebuffer(win_w, win_h);

  glBindFramebuffer(GL_FRAMEBUFFER, frame_buff_id);
  glBindVertexArray(vao_main);
  glUseProgram(main_program);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glBindVertexArray(vao_frame);
  glUseProgram(frame_program);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glfwSwapBuffers(win_ptr);
  while (!glfwWindowShouldClose(win_ptr))
  {
    glfwPollEvents();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
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
