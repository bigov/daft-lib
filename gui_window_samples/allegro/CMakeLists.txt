#
# cmake --clean . && cmake -DCMAKE_BUILD_TYPE=Debug ../ && cmake --build .
# cmake --clean . && cmake -DCMAKE_BUILD_TYPE=Release ../ && cmake --build .
#
cmake_minimum_required( VERSION 3.0 )
find_package( PkgConfig REQUIRED )

SET( PROJECT_AUTHOR "bigov" )
SET( PROJECT_AUTHOR_EMAIL "bigov@yandex.ru" )

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Prevented in-tree built. Please create a build \
  directory outside of the source code and call cmake from there.")
endif()

project( DevTmp )
SET( EXEC_NAME "devtmp" )

SET( CMAKE_CXX_FLAGS "-m64 -std=c++17")

# Не отображать окно терминала
#SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -Wl,-subsystem,windows")

# Контроль ошибок при сборке
SET( CMAKE_VERBOSE_MAKEFILE OFF )
#SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexceptions -Wextra \
#  -Woverloaded-virtual -Wnon-virtual-dtor -Winit-self " )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

## Сборка без установки программ
SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )

# Исходные и подключаемые файлы (Relative paths are interpreted as relative
# to the current source directory)
file( GLOB SRC_CODE "*.cpp" )

pkg_search_module( ALLEGRO REQUIRED allegro-5 allegro-5.0)
pkg_search_module( ALLEGRO_FONT REQUIRED  allegro_font-5 allegro_font-5.0 )
pkg_search_module( ALLEGRO_TTF REQUIRED  allegro_ttf-5 allegro_ttf-5.0 )

add_executable( "${EXEC_NAME}" "${SRC_CODE}" )

target_link_libraries( "${EXEC_NAME}"
  "${ALLEGRO_LIBRARIES}" "${ALLEGRO_FONT_LIBRARIES}" "${ALLEGRO_TTF_LIBRARIES}"
  )

