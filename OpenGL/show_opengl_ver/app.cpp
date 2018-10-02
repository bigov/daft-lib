/**
 * app.cpp
 *
 * Tool for display the name of the using video renderer module,
 * and actual versions of the OpenGL and GLSL.
 *
 * dependens: GLFW
 *
 */
#include <iostream>
#include "gl_com_4_5.h"
#include <GLFW/glfw3.h>

#define ERR throw std::runtime_error

void _pause(void)
{
	std::cout << "\npress Enter ...";
	std::string n;
	std::getline(std::cin, n);
	return;
}

bool init_ogl(void)
{
	return ogl_LoadFunctions();
}

void test_profile( GLint profile )
{
	GLFWwindow * pWin = nullptr;
	std::string p_title;
	
	switch(profile)
	{
		case GLFW_OPENGL_ANY_PROFILE:
			p_title = "No profile";
			pWin = glfwCreateWindow(1, 1, "", NULL, NULL);	
			break;
		case GLFW_OPENGL_COMPAT_PROFILE:
			p_title = "Compatibility profile";
			glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
			break;
		case GLFW_OPENGL_CORE_PROFILE:
			p_title = "Core profile";
			glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
	}

	GLint vMAJ = 5, vMIN = 0;
	glfwWindowHint(GLFW_VISIBLE, false);
	
	std::cout << p_title << '\n'
		<< "-----------------------------------------\n";


	while (nullptr == pWin && vMAJ > 0)
	{
		vMIN -= 1; if (vMIN < 0) { vMIN = 9; vMAJ -= 1; } // start from ver. 4.9
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, vMAJ);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, vMIN);
		pWin = glfwCreateWindow(1, 1, "", NULL, NULL);	
	}
	
	if (nullptr == pWin) 
	{
		std::cout << "  Can't use this OpenGL profile.\n\n";
		return;
	}

	glfwMakeContextCurrent(pWin);
	static bool ogl_Load = init_ogl();
	if (!ogl_Load) ERR("Can't load OpenGl finctions");

  GLint major = 0; glGetIntegerv(GL_MAJOR_VERSION, &major);
	GLint minor = 0; glGetIntegerv(GL_MINOR_VERSION, &minor);
	
	std::cout 
		<< "  video system : "
		<< glGetString(GL_RENDERER) << '\n'
		<< "  vendor info  : "
		<< glGetString(GL_VERSION)  << '\n'
		<< "  OpenGL ver.  : " <<	major << "." << minor << '\n'
		<< "  GLSL version : " << glGetString(GL_SHADING_LANGUAGE_VERSION)<<"\n\n";
	
	glfwDestroyWindow(pWin);
	return;
}

void show_opengl_version(void)
{
	if (!glfwInit()) ERR("Error init GLFW lib.");
	std::cout << '\n';
	test_profile(GLFW_OPENGL_ANY_PROFILE);
	std::cout << '\n';
	test_profile(GLFW_OPENGL_COMPAT_PROFILE);
	std::cout << '\n';
	test_profile(GLFW_OPENGL_CORE_PROFILE);
}

int main( void )
{
	try { 
		show_opengl_version();
	} catch(std::exception & e)	{
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	} catch(...) {
		std::cout << "FAILURE: undefined exception." << '\n';
		_pause();	
		return EXIT_FAILURE;
	}
	_pause();	
	return EXIT_SUCCESS;
}

