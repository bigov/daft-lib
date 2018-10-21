#include "a_win.hpp"
#include "gl_tools.hpp"

//### Отображение контента
void draw_scene(void)
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
    if(!gladLoadGL()) { ERR("FAILURE: can't load GLAD."); }
    std::cout << "OpenGL Version " << GLVersion.major
      << " " << GLVersion.minor << " loaded\n";
    gl_init_program();
    gl_init_scene();
    while(window_run()) draw_scene();
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
