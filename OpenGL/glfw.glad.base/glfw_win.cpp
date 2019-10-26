#include "glfw_win.hpp"

GLFWwindow* MainWin = nullptr;
GLFWwindow* ThWin = nullptr;

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

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

  glfwWindowHint(GLFW_VISIBLE, false);
  ThWin = glfwCreateWindow(1, 1, "", NULL, NULL);
  if (nullptr == ThWin) throw std::runtime_error("Creating Window ThWin fail.");

  glfwWindowHint(GLFW_VISIBLE, true);
  MainWin = glfwCreateWindow(500, 400, "OpenGL learn", NULL, ThWin);
  if (nullptr == MainWin) throw std::runtime_error("Creating Window pWin fail.");

  glfwMakeContextCurrent(MainWin);
  if(!gladLoadGL()) { ERR("FAILURE: can't load GLAD."); }
  glfwSwapInterval(0);
  glfwSetKeyCallback(MainWin, key_callback);

  return;
}

//### Оконный цикл
void window_update(void)
{
  fps++;
  if(std::chrono::system_clock::now() - t_start > t_1)
  {
    glfwSetWindowTitle(MainWin, std::to_string(fps).c_str());
    t_start = std::chrono::system_clock::now();
    fps = 0;
  }
  glfwSwapBuffers(MainWin);
  glfwPollEvents();
  return;
}

//### Очистка памяти
void window_destroy(void)
{
  glfwDestroyWindow(MainWin);
  glfwDestroyWindow(ThWin);
  return;
}

bool window_run(void)
{
  return !glfwWindowShouldClose(MainWin);
}

