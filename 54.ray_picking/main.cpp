/*
* OpenGL ray picking
*
* Copyright (C) 2016 by Sascha Willems - www.saschawillems.de
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "glRenderer.h"

glRenderer renderer;

const std::string appTitle = "OpenGL example - Ray picking";

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	renderer.keyCallback(key, scancode, action, mods);
}

static void mouse_callback(GLFWwindow* window, int button, int action, int mod)
{
	renderer.mouseButtonCallback(button, action);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(1280, 720, appTitle.c_str(), NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	if(!ogl_LoadFunctions()) fprintf(stderr, "Can't load OpenGl finctions");
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowPos(window, 512, 400);
	glfwSwapInterval(0);

	std::cout
		<< "Vendor: "   << glGetString(GL_VENDOR)   << "\n"
		<< "Renderer: " << glGetString(GL_RENDERER) << "\n"
		<< "Version: "  << glGetString(GL_VERSION)  << "\n\n";

	renderer = glRenderer();
	renderer.window = window;
	renderer.generateBuffers();
	renderer.generateShaders();

	glDisable(GL_CULL_FACE);

	double lastFPStime = glfwGetTime();
	double lastFrameTime = glfwGetTime();
	int frameCounter = 0;

	//Main Loop
	do
	{
		double thisFPStime = glfwGetTime();
		frameCounter++;

		if (thisFPStime - lastFPStime >= 1.0)
		{
			lastFPStime = thisFPStime;
			std::string windowTitle = appTitle +" (";
			windowTitle += std::to_string(frameCounter);
			windowTitle += " fps) - 2016 by Sascha Willems (www.saschawillems.de)";
			const char* windowCaption = windowTitle.c_str();
			glfwSetWindowTitle(window, windowCaption);
			frameCounter = 0;
		}

		double currTime = glfwGetTime();
		renderer.renderScene(currTime - lastFrameTime);
		lastFrameTime = currTime;
		glfwPollEvents();

	} while (!glfwWindowShouldClose(window));

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
