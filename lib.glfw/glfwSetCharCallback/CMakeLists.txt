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

project( "glfw3 and glad tests" )
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

# Настройка переменной пути к ${TP_LIBS}
include( "../../deps/tplibs.cmake" )
include_directories( SYSTEM "${TP_LIBS}" )

# Подключение библиотек
SET( LIB_GLFW "${TP_LIBS}/GLFW/bin.mingw.64/glfw3.dll" )
SET( LIB_GLAD "${TP_LIBS}/glad/bin.mingw.64/glad.dll" )

# Исходные файлы
file( GLOB SRC_CODE
    "main.cpp"
    "glfw_win.cpp"
    "gl_tools.cpp"
    )

add_executable( "${EXEC_NAME}" "${SRC_CODE}" )
target_link_libraries( "${EXEC_NAME}" "${LIB_GLAD}" "${LIB_GLFW}" )

file( COPY "${LIB_GLFW}" DESTINATION "${CMAKE_BINARY_DIR}/" )
file( COPY "${LIB_GLAD}" DESTINATION "${CMAKE_BINARY_DIR}/" )

