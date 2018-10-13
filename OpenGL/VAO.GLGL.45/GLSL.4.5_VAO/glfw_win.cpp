#include "glfw_win.hpp"

GLFWwindow* pWin;

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

