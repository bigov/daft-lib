#ifndef __WIN_HPP__
#define __WIN_HPP__

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern void opengl_window_show(const unsigned char* texture_data, uint32_t win_width, uint32_t win_height);
void savePNG(uint8_t *image, int32_t width, int32_t height);

#endif // __WIN_HPP__
