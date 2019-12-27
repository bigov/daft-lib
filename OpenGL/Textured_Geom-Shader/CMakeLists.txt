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

project( "Learn geometric shaders" )
SET( EXEC_NAME "bin-go" )

if(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  # Не отображать окно терминала
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -Wl,-subsystem,windows")
endif(CMAKE_BUILD_TYPE STREQUAL "Release")

# Контроль ошибок при сборке
SET( CMAKE_VERBOSE_MAKEFILE OFF )

## Сборка без установки программ
SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -m64 -march=x86-64 \
  -Werror -Wall -Wextra -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy \
  -Wnon-virtual-dtor -Wconversion -Wsign-conversion -Winit-self \
  -Wunreachable-code -Weffc++ -Wold-style-cast" )

find_package( PkgConfig REQUIRED )
pkg_check_modules( GLFW REQUIRED glfw3 )
pkg_check_modules( PNG REQUIRED libpng16 )

# Настройка ${TP_LIBS} - путь к локальной библиотеке
include( "../../deps/tplibs.cmake" )

# Компилируемые библиотеки
# ------------------------
# GlLoadLib
add_subdirectory( "${TP_LIBS}/glcore33" "glcore33" EXCLUDE_FROM_ALL)

# список исходников
file( GLOB trSRC "${CMAKE_SOURCE_DIR}/src/*.cpp" )

## Список библиотек
SET( MY_LIBS ${GLFW_LIBRARIES} ${PNG_LIBRARIES} pthread stdc++fs glcore33 )

add_executable( ${EXEC_NAME} ${trSRC} )
target_link_libraries( ${EXEC_NAME} ${MY_LIBS} )
