/* filename: gl_tools.hpp
 *
 */
#ifndef gl_tools_hpp
#define gl_tools_hpp

#include "main.hpp"

extern GLuint hdl_VAO;
extern GLuint pos_Buf;
extern GLuint col_Buf;

extern std::atomic<bool> on_run;

void gl_draw_arrays(void);
void gl_init_program(void);
void gl_init_scene(void);
void gl_data_shake(GLuint, GLuint, GLFWwindow*);

#endif
