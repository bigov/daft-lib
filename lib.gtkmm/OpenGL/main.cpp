/* Filename: main.cpp
 *
 */
#include "glarea.hpp"

GLint  mvp_id = 0;
GLuint vao = 0;
GLuint vbo = 0;
GLuint program = 0;

GLfloat vertex_data[] =
{
  0.f,   0.5f,   0.f, 1.f,
  0.5f, -0.366f, 0.f, 1.f,
 -0.5f, -0.366f, 0.f, 1.f,
};

///----------------------------------------------------------------------------
/// \brief compute_mvp
/// \param res
/// \param phi
/// \param theta
/// \param psi
///
void compute_mvp(float *res, float phi, float theta, float psi)
{
  float x       {phi * ((float)G_PI / 180.f)};
  float y       {theta * ((float)G_PI / 180.f)};
  float z       {psi * ((float)G_PI / 180.f)};
  float c1      {cosf (x)};
  float s1      {sinf (x)};
  float c2      {cosf (y)};
  float s2      {sinf (y)};
  float c3      {cosf (z)};
  float s3      {sinf (z)};
  float c3c2    {c3 * c2};
  float s3c1    {s3 * c1};
  float c3s2s1  {c3 * s2 * s1};
  float s3s1    {s3 * s1};
  float c3s2c1  {c3 * s2 * c1};
  float s3c2    {s3 * c2};
  float c3c1    {c3 * c1};
  float s3s2s1  {s3 * s2 * s1};
  float c3s1    {c3 * s1};
  float s3s2c1  {s3 * s2 * c1};
  float c2s1    {c2 * s1};
  float c2c1    {c2 * c1};

  /* apply all three rotations using the three matrices:
   *
   * ⎡  c3 s3 0 ⎤ ⎡ c2  0 -s2 ⎤ ⎡ 1   0  0 ⎤
   * ⎢ -s3 c3 0 ⎥ ⎢  0  1   0 ⎥ ⎢ 0  c1 s1 ⎥
   * ⎣   0  0 1 ⎦ ⎣ s2  0  c2 ⎦ ⎣ 0 -s1 c1 ⎦
   */
  res[0] = c3c2;  res[4] = s3c1 + c3s2s1;  res[8] = s3s1 - c3s2c1; res[12] = 0.f;
  res[1] = -s3c2; res[5] = c3c1 - s3s2s1;  res[9] = c3s1 + s3s2c1; res[13] = 0.f;
  res[2] = s2;    res[6] = -c2s1;         res[10] = c2c1;          res[14] = 0.f;
  res[3] = 0.f;   res[7] = 0.f;           res[11] = 0.f;           res[15] = 1.f;
}

///----------------------------------------------------------------------------
/// Компиляция GLSL шейдера
///
GLuint create_shader( unsigned int type, Glib::RefPtr<const Glib::Bytes> src )
{
  gsize size = src->get_size();
  auto ch = static_cast<const GLchar*>(src->get_data(size));
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &ch, nullptr);
  glCompileShader(shader);

  int status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if(status == GL_FALSE)
  {
    int log_len;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

    std::vector<GLchar> log_space(static_cast<unsigned int>(log_len+1), ' ' );
    glGetShaderInfoLog(shader, log_len, nullptr, log_space.data());

    std::cerr << "Compile failure in " <<
      (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<
      " shader: " << log_space.data() << std::endl;

    glDeleteShader(shader);
    return 0;
  }
  return shader;
}

///----------------------------------------------------------------------------
/// \brief init_buffers
///
void init_buffers(void)
{
  glClearColor(0.7, 0.8, 0.9, 1.0);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

///----------------------------------------------------------------------------
/// \brief init_shaders
///
void init_shaders(void)
{
  auto bytes = Gio::Resource::lookup_data_global("/glsl/vertex.glsl");
  if(!bytes)
  {
    std::cerr << "Failed fetching vertex shader resource" << std::endl;
    program = 0;
    return;
  }
  auto vertex = create_shader(GL_VERTEX_SHADER, bytes);
  if(vertex == 0)
  {
    program = 0;
    return;
  }

  bytes = Gio::Resource::lookup_data_global("/glsl/fragment.glsl");
  if(!bytes)
  {
    std::cerr << "Failed fetching fragment shader resource" << std::endl;
    glDeleteShader(vertex);
    program = 0;
    return;
  }
  auto fragment = create_shader(GL_FRAGMENT_SHADER, bytes);
  if(fragment == 0)
  {
    glDeleteShader(vertex);
    program = 0;
    return;
  }

  program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glLinkProgram(program);

  int status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if(status == GL_FALSE)
  {
    int log_len;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

    std::vector<GLchar> log_space(static_cast<unsigned int>(log_len+1), ' ');
    glGetProgramInfoLog(program, log_len, nullptr, log_space.data());

    std::cerr << "Linking failure: " << log_space.data() << std::endl;

    glDeleteProgram(program);
    program = 0;
  }
  else
  {
    /* Get the location of the "mvp" uniform */
    mvp_id = glGetUniformLocation(program, "mvp");

    glDetachShader(program, vertex);
    glDetachShader(program, fragment);
  }
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

///----------------------------------------------------------------------------
/// \brief draw_triangle
///
void draw_triangle(void)
{
  static float x = 0.f, y = 0.f, z = 0.f;
  float mvp[16];
  z += 1.f;
  compute_mvp(mvp, x, y, z);

  glUseProgram(program);
  glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0]);

  glBindBuffer(GL_ARRAY_BUFFER, vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glUseProgram(0);
}

///----------------------------------------------------------------------------
/// \brief render
/// \return
///
bool render_gl_content(const Glib::RefPtr<Gdk::GLContext>& /* context */)
{
   glClear(GL_COLOR_BUFFER_BIT);
   draw_triangle();
   glFlush();
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
  init_buffers();
  init_shaders();

  return app->run(OpenGLWindow);
}
