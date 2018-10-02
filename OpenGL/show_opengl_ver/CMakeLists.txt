# Сборка приложения:
#
# Под Windows:
# > cmake ../dev -G "MinGW Makefiles"
#
# На Linux
# $ cmake ../dev
#
# Потом (для всех)
# 	cmake --build .
#
# https://cmake.org/Wiki/CMake_Useful_Variables
#
cmake_minimum_required( VERSION 3.0 )	 # Проверка версии CMake.
project( show_opengl )
SET( CMAKE_VERBOSE_MAKEFILE OFF )
SET( CMAKE_BUILD_TYPE Release )

# Компилируемые библиотеки
include( "${CMAKE_SOURCE_DIR}/glfw.cmake" )

###
#  Устанока параметров для сборки в MinGW-W64 под MS Windows
#
if( (${MINGW}) AND (${CMAKE_SYSTEM_NAME} MATCHES "Windows") )
# -mwindows -Wl,-subsystem,windows
SET( CMAKE_CXX_FLAGS "--static \
 -fexceptions -std=c++14 -Werror -Wall -Wextra -Wpedantic\
 -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor -Wconversion\
 -Winit-self -Wunreachable-code -Weffc++" )
### [ -Wold-style-cast -Wsign-conversion ] отключены из-за glLoadGen ##

SET( LIBS mingw32 opengl32 z m gdi32 )
endif( (${MINGW}) AND (${CMAKE_SYSTEM_NAME} MATCHES "Windows") )

###
#  Устанока параметров для сборки на Linux
#
if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
SET( CMAKE_CXX_FLAGS "-I/usr/include/freetype2 -fexceptions\
 -std=c++14 -Werror -Wall -Wextra -Wpedantic -Woverloaded-virtual\
 -Wctor-dtor-privacy -Wnon-virtual-dtor -Wconversion\
 -Winit-self -Wunreachable-code -Weffc++ -Iinclude -Ideps" )
SET( LIBS glfw GL )
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

# Исполняемый файл приложения
add_executable( show_opengl app.cpp gl_com_4_5.c )

# Сборка приложения - линковка с библиотеками
target_link_libraries( show_opengl glfw ${LIBS} )

