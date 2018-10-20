# https://cmake.org/Wiki/CMake_Useful_Variables
#
# cmake --clean . && cmake -DCMAKE_BUILD_TYPE=Debug ../ && cmake --build . --target all
# cmake --clean . && cmake -DCMAKE_BUILD_TYPE=Release ../ && cmake --build . --target all
#

cmake_minimum_required( VERSION 3.0 )
project( SamplesDemos )
set(PROJECT_AUTHOR "bigov")
set(PROJECT_AUTHOR_EMAIL "bigov@yandex.ru")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Prevented in-tree built. Please create a build \
  directory outside of the source code and call cmake from there. Thank you.")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

## без установки программ
SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )
SET( CMAKE_VERBOSE_MAKEFILE OFF )

# Настройка переменной пути к ${TP_LIBS}
include( "../../deps/CMakeLists.txt" )
include_directories( SYSTEM "${TP_LIBS}" )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -Wall -Wextra \
  -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor  \
  -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code -Weffc++  \
  -Wold-style-cast" )

SET( LIB_GLAD "${TP_LIBS}/glad.dll" )
SET( LIB_GLFW "${TP_LIBS}/glfw3.dll" )

add_executable( simple "simple.cpp" )
target_link_libraries( simple "${LIB_GLFW}" "${LIB_GLAD}" )

file( COPY "${LIB_GLFW}" DESTINATION "${CMAKE_BINARY_DIR}/" )
file( COPY "${LIB_GLAD}" DESTINATION "${CMAKE_BINARY_DIR}/" )

