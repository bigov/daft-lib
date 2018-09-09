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
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ERR throw std::runtime_error

extern GLFWwindow * pWin;
extern GLuint shaderProgram;

extern void init_opengl_content(void);

#endif //__TOOLS_HPP__
