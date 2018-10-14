#include "glfw_win.hpp"

GLFWwindow* pWin;

int fps = 0;
std::chrono::seconds t_1(1);
std::chrono::time_point<std::chrono::system_clock> t_start =
  std::chrono::system_clock::now();

//### GLFW обработчик ошибок
void error_callback(int error, const char* description)
{
  std::cout << "GLFW error " << error << ": " << description;
  return;
}

//### GLFW обработчик клавиатуры
void key_callback(GLFWwindow* window, int key, int, int ac, int)
{
  if (key == GLFW_KEY_ESCAPE && ac == GLFW_RELEASE)
    glfwSetWindowShouldClose(window, true);
  return;
}

//### Создание окна
void window_create(void)
{
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) throw std::runtime_error("Error init GLFW lib.");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  pWin = glfwCreateWindow(1024, 800, "GLSL learn", NULL, NULL);
  if (nullptr == pWin) throw std::runtime_error("Creating Window fail.");
  glfwMakeContextCurrent(pWin);
  glfwSwapInterval(0);
  glfwSetKeyCallback(pWin, key_callback);
  return;
}

//### Оконный цикл
void window_update(void)
{
  fps++;
  if(std::chrono::system_clock::now() - t_start > t_1)
  {
    glfwSetWindowTitle(pWin, std::to_string(fps).c_str());
    t_start = std::chrono::system_clock::now();
    fps = 0;
  }
  glfwSwapBuffers(pWin);
  glfwPollEvents();
  return;
}

//### Очистка памяти
void window_destroy(void)
{
  glfwDestroyWindow(pWin);
  return;
}

bool window_run(void)
{
  return !glfwWindowShouldClose(pWin);
}

