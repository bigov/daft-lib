/*
* OpenGL ray picking
*
* Copyright (C) 2016 by Sascha Willems - www.saschawillems.de
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once

#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Windows.h>

#include <time.h> 
#include <array>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class glRenderer
{
private:
	std::vector<glm::vec3> triangleData;
	GLuint shader;
	GLuint VBO[2];
	GLuint IBO;
	GLuint UBO;
	uint32_t indexCount;
	float zoom = -2.0f;
	glm::vec3 rotation = glm::vec3(0.0f);
	GLuint loadShader(const char* vertexShaderFile, const char* fragmentShaderFile);
	void printProgramLog(GLuint shader);
	void printShaderLog(GLuint program);
	uint32_t instanceCount;
public:
	bool paused = false;
	GLFWwindow* window;
	glRenderer() {};
	~glRenderer() {};
	void generateShaders();
	void updateUBO();
	void generateBuffers();
	void renderScene(double deltaT);
	void keyCallback(int key, int scancode, int action, int mods);
	void mouseButtonCallback(int button, int action);
};

