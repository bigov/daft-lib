#
# TrickRig udp server
#

set(PROJECT_AUTHOR "bigov")
set(PROJECT_AUTHOR_EMAIL "bigov@yandex.ru")

cmake_minimum_required( VERSION 3.2 )
project( server VERSION 0.0.1 )
SET( EXEC_NAME server )

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

## Пока работаем без установки программы
SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )

SET( SRV_SRC "server.cpp" )

find_package( PkgConfig REQUIRED )
pkg_check_modules( UV REQUIRED libuv )

add_executable( ${EXEC_NAME} ${SRV_SRC} )
target_link_libraries( ${EXEC_NAME} ${UV_LIBRARIES} )
