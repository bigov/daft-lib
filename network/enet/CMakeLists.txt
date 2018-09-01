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
project( enetwrap )
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

# серверная часть
SET( SRV_SRC
  "${CMAKE_SOURCE_DIR}/server.cpp"
  "${CMAKE_SOURCE_DIR}/enetw.cpp"
)

# управление/контроль
SET( CTRL_SRC
  "${CMAKE_SOURCE_DIR}/ctrl.cpp"
  "${CMAKE_SOURCE_DIR}/enetw.cpp"
)

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17"  )

add_subdirectory( "${CMAKE_SOURCE_DIR}/.extlibs/enet" "enet" EXCLUDE_FROM_ALL)
include_directories( "${CMAKE_SOURCE_DIR}/.extlibs/enet/include" )

find_package( PkgConfig REQUIRED )
pkg_check_modules( NCURSESW REQUIRED ncursesw )

add_executable( server ${SRV_SRC} )
target_link_libraries( server enet ${NCURSESW_LIBRARIES} )

add_executable( ctrl ${CTRL_SRC} )
target_link_libraries( ctrl enet ${NCURSESW_LIBRARIES} )
