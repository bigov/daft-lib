#
# https://cmake.org/Wiki/CMake_Useful_Variables
#
# -DCMAKE_BUILD_TYPE=Release
#
cmake_minimum_required( VERSION 3.0 )
project( GtkmmLearn )
set(PROJECT_AUTHOR "bigov")
set(PROJECT_AUTHOR_EMAIL "bigov@yandex.ru")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Prevented in-tree built. Please create a build \
  directory outside of the source code and call cmake from there. Thank you.")
endif()

SET(CMAKE_BUILD_TYPE Debug)
SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )
SET( CMAKE_VERBOSE_MAKEFILE OFF )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O0 -Werror -Wall -Wextra" )
#  -Werror -Wall -Wextra \
#  -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor \
#  -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code -Weffc++ \
#  -Wold-style-cast" )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -Wl,-subsystem,windows" )
  # SET( TR_LIBS mingw32 gdi32 )
endif()

find_package( PkgConfig REQUIRED )
pkg_check_modules( GTKMM REQUIRED gtkmm-3.0 )
link_directories( ${GTKMM_LIBRARY_DIRS} )
include_directories( ${GTKMM_INCLUDE_DIRS} )

SET( APP "bin-go" )
file( GLOB SRC_FILES "*.cpp" )
add_executable( ${APP} "${SRC_FILES}" )
target_link_libraries( ${APP} ${TR_LIBS} ${GTKMM_LIBRARIES} )

