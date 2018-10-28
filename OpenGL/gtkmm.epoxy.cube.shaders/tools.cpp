/* filename: tools.cpp
 *
 * Набор функций для создания контента и компиляции шейдера
 *
 */
#include "tools.hpp"
#include "shaders.hpp"

GLuint shaderProgram = 0;

//### обработчик ошибок
void error_callback(int n, const char* descr)
{
  ERR(std::string("\n[GLFW] error "+std::to_string(n)+": "+descr+'\n'));
  return;
}

//## компиялция шейдера с контролем результата
void compile_shader(GLuint shader)
{
  glCompileShader(shader);
  GLint result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if(GL_FALSE == result)
  {
    GLint logLen;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
    if(logLen)
    {
      char * log = new char[logLen];
      GLsizei written;
      glGetShaderInfoLog(shader, logLen, &written, log);
      std::cout << log << '\n';
      delete [] log;
    }
    ERR("Error compile SHADER");
  }
  return;
}

//### Компиляция и запуск GLSL программы
void init_program(void)
{
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  if (!vertShader) ERR("Error create GL_VERTEX_SHADER");
  glShaderSource(vertShader, 1, &vert_shader, NULL);
  compile_shader(vertShader);

  GLuint geomShader = glCreateShader(GL_GEOMETRY_SHADER);
  if (!geomShader) ERR("Error create GL_GEOMETRY_SHADER");
  glShaderSource(geomShader, 1, &geom_shader, NULL);
  compile_shader(geomShader);

  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  if (!fragShader) ERR("Error create GL_FRAGMENT_SHADER");
  glShaderSource(fragShader, 1, &frag_shader, NULL);
  compile_shader(fragShader);

  shaderProgram = glCreateProgram();
  if (!shaderProgram) ERR("Error creating GLSL program\n");

  glAttachShader(shaderProgram, vertShader);
  glAttachShader(shaderProgram, geomShader);
  glAttachShader(shaderProgram, fragShader);
  glLinkProgram(shaderProgram);
  GLint status;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
  if (GL_FALSE == status)
  {
    GLint logLen;
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen)
    {
      char * log = new char[logLen];
      GLsizei written;
      glGetProgramInfoLog(shaderProgram, logLen, &written, log);
      std::cout << log << '\n';
      delete [] log;
    }
    ERR("Failed to link GLSL program.\n");
  }
  glUseProgram(shaderProgram);

  return;
}

// индекс атрибута шейдерной программы
GLuint get_attrib_location(const char * attr)
{
  GLint posAttrib = glGetAttribLocation(shaderProgram, attr);
  std::string attr_name(attr);
  if (0 > posAttrib) ERR(std::string("Can't get attrib: " + attr_name));
  return static_cast<GLuint>(posAttrib);
}

// индекс Unform-переменной шейдерной программы
GLint get_uniform_location(const char * attr)
{
  GLint posAttrib = glGetUniformLocation(shaderProgram, attr);
  std::string attr_name(attr);
  if (0 > posAttrib) ERR(std::string("Can't get uniform: " + attr_name));
  return posAttrib;
}
