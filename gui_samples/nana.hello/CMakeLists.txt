#
# https://cmake.org/Wiki/CMake_Useful_Variables
#
# -DCMAKE_BUILD_TYPE=Release
#
cmake_minimum_required( VERSION 3.0 )
project( NanaLearn )
set(PROJECT_AUTHOR "bigov")
set(PROJECT_AUTHOR_EMAIL "bigov@yandex.ru")
SET( APP "bin-go" )
file( GLOB APP_SRC "*.cpp" )

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Prevented in-tree built. Please create a build \
  directory outside of the source code and call cmake from there. Thank you.")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

## Работать без установки программы
SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )
SET( CMAKE_VERBOSE_MAKEFILE OFF )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )
#  -Werror -Wall -Wextra \
#  -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor \
#  -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code -Weffc++ \
#  -Wold-style-cast" )

include("../../deps/tplibs.cmake")

include_directories( "${TP_LIBS}/SRC/nana-1.6.2/include" )
#option(NANA_CMAKE_SHARED_LIB "Compile nana as a shared library." ON)
#option(NANA_CMAKE_STD_FILESYSTEM_FORCE "Use of STD filesystem?(a compilation\
#  error will ocurre if not available)" ON)
add_subdirectory( "${TP_LIBS}/SRC/nana-1.6.2" "nana" EXCLUDE_FROM_ALL )
link_directories( "${CMAKE_BINARY_DIR}/nana" )

add_executable( "${APP}" "${APP_SRC}" )
target_link_libraries( "${APP}" nana )

