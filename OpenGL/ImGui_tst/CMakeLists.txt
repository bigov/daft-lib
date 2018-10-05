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
project( triangle )
set(PROJECT_AUTHOR "bigov")
set(PROJECT_AUTHOR_EMAIL "bigov@yandex.ru")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

## Пока работаем без установки программы
SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )
SET( CMAKE_VERBOSE_MAKEFILE OFF )

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_CUSTOM="gl_core33.h")

# Исходные и подключаемые файлы
file( GLOB APP_SRC_FILES
  "${CMAKE_SOURCE_DIR}/*.cpp"
  "${CMAKE_SOURCE_DIR}/../.extlibs/imgui/*.cpp"
  "${CMAKE_SOURCE_DIR}/../.extlibs/imgui/examples/imgui_impl_glfw.cpp"
  "${CMAKE_SOURCE_DIR}/../.extlibs/imgui/examples/imgui_impl_opengl3.cpp"
  )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )
include_directories( "${CMAKE_SOURCE_DIR}/../.extlibs/glcore33"
                     "${CMAKE_SOURCE_DIR}/../.extlibs/glfw/include"
                     "${CMAKE_SOURCE_DIR}/../.extlibs/glfw/deps"
                     "${CMAKE_SOURCE_DIR}/../.extlibs/imgui"
)
# библиотека GLFW
SET( GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE )
SET( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE )
SET( GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE )
SET( GLFW_DOCUMENT_INTERNALS OFF CACHE BOOL "Build the GLFW document" FORCE )
SET( GLFW_INSTALL OFF CACHE BOOL "Build the GLFW install" FORCE )
SET( GLFW_USE_MIR OFF CACHE BOOL "Build the GLFW with Mir" FORCE )
SET( GLFW_USE_OSMESA OFF CACHE BOOL "Build the GLFW with os mesa" FORCE )
SET( GLFW_USE_WAYLAND OFF CACHE BOOL "Build the GLFW with Wayland server" FORCE )
SET( GLFW_VULKAN_STATIC OFF CACHE BOOL "Use the Vulkan" FORCE )
add_subdirectory( "${CMAKE_SOURCE_DIR}/../.extlibs/glfw" "glfw" EXCLUDE_FROM_ALL)

add_subdirectory( "${CMAKE_SOURCE_DIR}/../.extlibs/glcore33" "glcore33" EXCLUDE_FROM_ALL)

add_executable( triangle "${APP_SRC_FILES}" )
target_link_libraries( triangle glfw glcore33 )

