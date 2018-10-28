//----------------------------------------------------------------------------
//
// file: tools.hpp
//
// Набор функций, необходимый  для создания контента и компиляции шейдера
// 
//----------------------------------------------------------------------------
#ifndef __TOOLS_HPP__
#define __TOOLS_HPP__

#include <iostream>
#include <chrono>

#include "gl_core_3_3.h"
#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ERR throw std::runtime_error

extern GLFWwindow * pWin;
extern GLuint shaderProgram;

extern void init_opengl_content(void);
extern GLuint get_attrib_location(const char *);
extern GLint get_uniform_location(const char *);

#endif //__TOOLS_HPP__
