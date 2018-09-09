//============================================================================
//
// file: main.hpp
//
// Подключаем все внешние модули из одного места
//
//============================================================================
#ifndef __MAIN_HPP__
#define __MAIN_HPP__

//#define NDEBUG // в релизе все проверки можно отключить
#include <cassert>
#include <chrono>
#include <memory>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <valarray>
//#include <initializer_list>
#include <unordered_map>

#include <gl_core33.h>
#include <GLFW/glfw3.h>
#include <png.h>
#include <ft2build.h>
#include <freetype/freetype.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/integer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ERR throw std::runtime_error

#endif


