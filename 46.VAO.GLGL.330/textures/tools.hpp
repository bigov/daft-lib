#include <iostream>
#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>
#include "image.c" 

#define ERR throw std::runtime_error

void compile_shader(GLuint shader);
void error_callback(int error, const char* description);
void init_program(const GLchar * vert_shader, const GLchar * frag_shader);
void key_callback(GLFWwindow* window, int key, int sc, int ac, int md);
GLFWwindow * open_window(void);

