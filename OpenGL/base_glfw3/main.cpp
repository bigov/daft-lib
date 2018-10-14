#include "gl_tools.hpp"
#include "glfw_win.hpp"

//### Отображение контента
void gl_draw_scene(void)
{
  gl_draw_arrays();
  window_update();
  return;
}

int main(int, char**)
{
  try
  {
    window_create();
    gl_init_program();
    gl_init_scene();
    while(window_run()) gl_draw_scene();
    window_destroy();
  }
  catch(std::exception & e)
  {
    std::cout << e.what() << '\n';;
    return EXIT_FAILURE;
  }
  catch(...) { return EXIT_FAILURE; }

  return EXIT_SUCCESS;
}
