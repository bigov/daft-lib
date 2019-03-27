#
# cmake --clean . && cmake -DCMAKE_BUILD_TYPE=Debug ../ && cmake --build .
# cmake --clean . && cmake -DCMAKE_BUILD_TYPE=Release ../ && cmake --build .
#
cmake_minimum_required( VERSION 3.0 )
SET( PROJECT_AUTHOR "bigov" )
SET( PROJECT_AUTHOR_EMAIL "bigov@yandex.ru" )

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Prevented in-tree built. Please create a build \
  directory outside of the source code and call cmake from there.")
endif()

project( render_in_buff )
SET( EXEC_NAME "test" )
include_directories("glad")

SET( CMAKE_CXX_FLAGS "-m64 -std=c++17 -lpthread")

# Не отображать окно терминала
#SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -Wl,-subsystem,windows")

# Контроль ошибок при сборке
SET( CMAKE_VERBOSE_MAKEFILE OFF )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexceptions -Wextra \
  -Woverloaded-virtual -Wnon-virtual-dtor -Winit-self " )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

## Сборка без установки программ
SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  # Windows specific code
  set(OperatingSystem "MS Windows")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  # Linux specific code
  SET(OperatingSystem "Linux")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Relative paths are interpreted as relative to the current source directory
SET (SRC_CODE main.cpp glad/glad.c)
#file(GLOB SHADERS "*.glsl")
#file(COPY ${SHADERS} DESTINATION ${CMAKE_BINARY_DIR})
#file(COPY "glsl" DESTINATION ${CMAKE_BINARY_DIR})

# Библиотека GLFW
find_package( PkgConfig REQUIRED )
pkg_check_modules( GLFW REQUIRED glfw3 )

add_executable( ${EXEC_NAME} ${SRC_CODE} )
target_link_libraries( ${EXEC_NAME} ${GLFW_LIBRARIES} )


