#include "glfw_win.hpp"
#include "gl_tools.hpp"

std::atomic<bool> on_run {true}; // Управление циклом во втором потоке

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
    gl_init_program();
    gl_init_scene();
    std::thread Shaker(gl_data_shake, hdl_VAO, col_Buf, ThWin);
    while(window_run()) draw_scene();
    on_run.store(false); // прервать цикл во втором потоке
    Shaker.join();
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
