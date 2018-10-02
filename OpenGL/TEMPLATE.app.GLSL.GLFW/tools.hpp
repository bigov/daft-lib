//----------------------------------------------------------------------------
//
// file: tools.hpp
//
// Набор функций, необходимый  для создания контента и компиляции шейдера
// 
//----------------------------------------------------------------------------
#ifndef __TOOLS_HPP__
#define __TOOLS_HPP__

// Размещение файлов шейдеров
#define TR_VERT_SHADER_FNAME "set/vert.glsl"
#define TR_GEOM_SHADER_FNAME "set/geom.glsl"
#define TR_FRAG_SHADER_FNAME "set/frag.glsl"

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

#include "lib/gl_core_3_3.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ERR throw std::runtime_error

extern GLFWwindow * pWin;
extern GLuint shaderProgram;

extern void init_opengl_content(void);
extern std::vector<char> get_txt_chars(const std::string & fname);

#endif //__TOOLS_HPP__
