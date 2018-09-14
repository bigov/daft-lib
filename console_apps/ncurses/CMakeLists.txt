#
# При вызове команды "cmake" (под win32) НЕОБХОДИМО указать тип сборки,
# например, для сборки в MinGW GCC указывается -
#
# -DCMAKE_BUILD_TYPE=Release ../ -G "MinGW Makefiles"
#
# Потом (для всех)
#   cmake --build .
#
#
# Под Linux можно собрать так:
#
# cmake --clean . && cmake -DCMAKE_BUILD_TYPE=Debug ../ && cmake --build . && ./app_dbg
# cmake --clean . && cmake -DCMAKE_BUILD_TYPE=Release ../ && cmake --build . && ./app_rel
#
# https://cmake.org/Wiki/CMake_Useful_Variables
#

cmake_minimum_required( VERSION 3.0 )
project( trcons )
set(PROJECT_AUTHOR "bigov")
set(PROJECT_AUTHOR_EMAIL "bigov@yandex.ru")
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()
SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )
SET( CMAKE_VERBOSE_MAKEFILE OFF )


# список исходников
file( GLOB CPPSRC "trcons.cpp" )

#-lpanelw -lncursesw" )
SET( CMAKE_CXX_FLAGS "-Wall" )

add_executable( trcons ${CPPSRC} )
target_link_libraries( trcons ncursesw )
