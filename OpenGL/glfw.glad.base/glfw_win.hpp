/* filename: glfw_win.hpp
 *
 */
#ifndef glfw_win_hpp
#define glfw_win_hpp

#include "main.hpp"

extern GLFWwindow* MainWin;
extern GLFWwindow* ThWin;

void window_create(void);
void window_update(void);
bool window_run(void);
void window_destroy(void);

#endif
