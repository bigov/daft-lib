cmake_minimum_required( VERSION 3.15 )
project( nuklear_demo_glfw_opengl3 )

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )
  message(FATAL_ERROR "Prevented in-tree built. Please create a build \
  directory outside of the source code and call cmake from there. Thank you.")
endif()

SET( BIN "demo" )
SET( CMAKE_BUILD_TYPE Debug )
SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )

include_directories("$(CMAKE_SOURCE_DIR)/../../../libs")

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++2a -Werror -Wall -Wextra \
  -Woverloaded-virtual -Winit-self -Wunreachable-code -Wpedantic" )

find_package( PkgConfig REQUIRED )
pkg_check_modules( GLFW REQUIRED glfw3 )

add_subdirectory( "$(CMAKE_SOURCE_DIR)/../../../libs/glad" "glad" EXCLUDE_FROM_ALL )
SET( LIBS "${GLFW_LIBRARIES}" glad )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -Wl,-subsystem,windows" )
endif()

if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
  SET( LIBS "${LIBS}" m GLU )
endif()

add_executable( ${BIN} "main.cpp" )
target_link_libraries( ${BIN} ${LIBS} )
