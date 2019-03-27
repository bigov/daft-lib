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
  framebuff = 0,
  vao_scene = 0,
  vao_frame = 0,
  program_scene  = 0,
  program_frame  = 0,
  scene_position = 0,
  scene_rgbcolor = 0,
  frame_position = 0,
  frame_texcoord = 0;

static GLint
  unif_texture = 0,
  unif_xid = 0;

static std::string
  scene_vert_glsl {"../glsl/main_vert.glsl"},
  scene_frag_glsl {"../glsl/main_frag.glsl"},
  frame_vert_glsl {"../glsl/buff_vert.glsl"},
  frame_frag_glsl {"../glsl/buff_frag.glsl"};

struct pixel_info { unsigned int Xid = 0, Yid = 0, Zid = 0; };

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


pixel_info read_pixel(GLint x, GLint y)
{
  glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuff);
  glReadBuffer(GL_COLOR_ATTACHMENT1);
  pixel_info Pixel;
  glReadPixels(x, y, 1, 1, GL_RGB_INTEGER, GL_UNSIGNED_INT, &Pixel);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
  return Pixel;
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


//## Программа рендера сцены
void init_pogram_scene()
{
  program_scene = create_program(scene_vert_glsl, scene_frag_glsl);
  glUseProgram(program_scene);
  scene_position = gl_get_attrib(program_scene, "VertexPosition");
  scene_rgbcolor = gl_get_attrib(program_scene, "VertexColor");
  unif_xid = gl_get_uniform(program_scene, "Xid");
  unsigned int x = 88888888;
  glUniform1ui(unif_xid, x);
  glUseProgram(0);
}


//## Программа рендера фрейма с текстурой кадра сцены
void init_pogram_frame()
{
  program_frame = create_program(frame_vert_glsl, frame_frag_glsl);
  glUseProgram(program_frame);
  frame_position = gl_get_attrib(program_frame, "VertexPosition");
  frame_texcoord = gl_get_attrib(program_frame, "TextureCoord");
  unif_texture = gl_get_uniform(program_frame, "texFramebuffer");
  // GL-номер основной текстуры фрейм-буфера для рендера сцены
  glUniform1i(unif_texture, 0); // GL_TEXTURE0 -> 0
  glUseProgram(0);
}

//## Основной VAO - рендер простой сцены в виде плоского треугольника
void init_vao_scene(void)
{                           //  x      y     z     r     g     b
  float pos_and_color[18] = { -0.8f, -0.8f, 0.0f, 0.4f, 1.0f, 0.4f,
                               0.8f, -0.8f, 0.0f, 1.0f, 0.4f, 0.4f,
                               0.0f,  0.8f, 0.0f, 1.0f, 1.0f, 0.4f };
  GLsizei stride = 6 * sizeof(GLfloat);

  glGenVertexArrays(1, &vao_scene);
  glBindVertexArray(vao_scene);

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pos_and_color), pos_and_color, GL_STATIC_DRAW);
  glEnableVertexAttribArray(scene_position);
  glEnableVertexAttribArray(scene_rgbcolor);
  glVertexAttribPointer(scene_position, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0*sizeof(GLfloat)));
  glVertexAttribPointer(scene_rgbcolor, 3, GL_FLOAT, GL_TRUE, stride, reinterpret_cast<void*>(3*sizeof(GLfloat)));
}

//## VAO прямоугольника, заполняющего окно приложения.
// На него натягивается текстура с кадром сцены.
void init_vao_frame(void)
{                        // x    y    U    V
  GLfloat Position[16] = {-1.f,-1.f, 0.f, 0.f,
                           1.f,-1.f, 1.f, 0.f,
                          -1.f, 1.f, 0.f, 1.f,
                           1.f, 1.f, 1.f, 1.f };
  GLsizei stride = 4 * sizeof(GLfloat);
  glGenVertexArrays(1, &vao_frame);
  glBindVertexArray(vao_frame);

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Position), Position, GL_STATIC_DRAW);
  glEnableVertexAttribArray(frame_position);
  glEnableVertexAttribArray(frame_texcoord);
  glVertexAttribPointer(frame_position, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0*sizeof(GLfloat)));
  glVertexAttribPointer(frame_texcoord, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(2*sizeof(GLfloat)));
}

bool init_framebuffer(GLsizei w, GLsizei h)
{
  GLint lod = 0, frame = 0;

  // Основная текстура (рендер кадра сцены)
  glActiveTexture(GL_TEXTURE0);
  GLuint tex0 = 0;
  glGenTextures(1, &tex0);
  glBindTexture(GL_TEXTURE_2D, tex0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, lod, GL_RGBA, w, h, frame, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  // Вспомогательная текстура (идентификация примитивов)
  glActiveTexture(GL_TEXTURE1);
  GLuint tex1 = 0;
  glGenTextures(1, &tex1);
  glBindTexture(GL_TEXTURE_2D, tex1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, lod, GL_RGB32UI, w, h, frame, GL_RGB_INTEGER, GL_UNSIGNED_INT, nullptr);

  glBindTexture(GL_TEXTURE_2D, 0);

  glGenFramebuffers(1, &framebuff);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuff);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex0, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, tex1, 0);

  GLenum b[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
  glDrawBuffers(2, b);

  //// DEPTH & STENCIL в данном примере не используется - отключено.
  //GLuint rbufid = 0;
  //glGenRenderbuffers(1, &rbufid);
  //glBindRenderbuffer(GL_RENDERBUFFER, rbufid);
  //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbufid);
  //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) return false;
  return glGetError() == GL_NO_ERROR;
}

//## ---
void show(GLFWwindow* win_ptr)
{
  GLint maxAttach = 0;
  glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttach);
  GLint maxDrawBuf = 0;
  glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuf);
  std::cout << "GL_MAX_DRAW_BUFFERS: " << maxDrawBuf << "\n"
            << "GL_MAX_COLOR_ATTACHMENTS: " << maxAttach << "\n\n";

  glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
  glDisable(GL_DEPTH_TEST);
  glViewport(0, 0, win_w, win_h);

  init_pogram_scene();
  init_pogram_frame();
  init_vao_scene();
  init_vao_frame();
  if (!init_framebuffer(win_w, win_h)) ERR ("Can't init FrameBuffer");

  glBindFramebuffer(GL_FRAMEBUFFER, framebuff);
  glBindVertexArray(vao_scene);
  glUseProgram(program_scene);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindVertexArray(vao_frame);
  glUseProgram(program_frame);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  auto Pixel = read_pixel(win_w/2, win_h/2);
  std::cout << "Xid = " << Pixel.Xid << "\n";

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
  std::cout << "\n";
  try {
    show(glfw_win());
  } catch(std::exception & e) {
    std::cout << e.what() << "\n";
    return EXIT_FAILURE;
  } catch(...) {
    std::cout << "FAILURE: undefined exception.\n";
    return EXIT_FAILURE;
  }
  std::cout << "\n\n";
  return EXIT_SUCCESS;
}
