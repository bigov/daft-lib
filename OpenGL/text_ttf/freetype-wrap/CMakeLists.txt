# https://cmake.org/Wiki/CMake_Useful_Variables
#
# cmake --clean . && cmake -DCMAKE_BUILD_TYPE=Debug ../ && cmake --build . --target all
# cmake --clean . && cmake -DCMAKE_BUILD_TYPE=Release ../ && cmake --build . --target all
#

cmake_minimum_required( VERSION 3.0 )

project(
  OpenGLTextOut VERSION "0.0.1.0"
  DESCRIPTION "OpenGL example show text"
  HOMEPAGE_URL "https://www.trickrig.net"
  LANGUAGES "CXX"
  )

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
include( "../../../deps/tplibs.cmake" )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -Wall -Wextra \
  -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor \
  -Wconversion -Winit-self -Wunreachable-code -Weffc++" )
#  -Wsign-conversion")
#" -Wold-style-cast" )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -Wl,-subsystem,windows" )
endif()

find_package( PkgConfig REQUIRED )

pkg_check_modules( FREETYPE2 REQUIRED freetype2 )
include_directories( ${FREETYPE2_INCLUDE_DIRS} )
SET( CMAKE_C_FLAGS "${FREETYPE2_CFLAGS_OTHER}" )

pkg_check_modules( PNG REQUIRED libpng )


if( ${MINGW} )
  SET( TR_LIBS mingw32 gdi32 )
endif()

pkg_check_modules( GLFW REQUIRED glfw3 )
add_subdirectory( "${TP_LIBS}/glad" "glad" EXCLUDE_FROM_ALL )

add_executable( ttf-show "main.cpp" "wft2.cpp" "win.cpp" )
target_link_libraries( ttf-show "${TR_LIBS}" "${GLFW_LIBRARIES}" "${PNG_LIBRARIES}"  "${FREETYPE2_LIBRARIES}" glad )

