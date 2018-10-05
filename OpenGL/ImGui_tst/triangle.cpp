#include "gl_console.hpp"

static void error_callback(int error, const char* description)
{
  std::cout << "Error "<< error << ": " << description << "\n";
  return;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  scancode += mods; //hide errors
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
     glfwSetWindowShouldClose(window, GLFW_TRUE);
  else std::cout << key << ", ";
  return;
}

int main(void)
{
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) exit(EXIT_FAILURE);
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  window = glfwCreateWindow(900, 700, "Simple example", nullptr, nullptr);
  if (!window) exit(EXIT_FAILURE);
  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
  if(!ogl_LoadFunctions()) exit(EXIT_FAILURE);
  glfwSwapInterval(1);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  int display_w, display_h;
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    static gl_console Console;
    bool run = true;
    Console.Draw("Test GL console", &run);

    ImGui::Render();
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
