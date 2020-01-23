#
# По-умолчанию используется GCC
#
# Если надо Clang, то запускаем так:
#   CC="clang" CXX="clang++" cmake ../ && cmake --build .

cmake_minimum_required( VERSION 3.15 )
project( SimpleTests )
SET( PROJECT_AUTHOR "bigov" )
SET( PROJECT_AUTHOR_EMAIL "bigov@yandex.ru" )
SET( APP "simple" )

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )
  message(FATAL_ERROR "Prevented in-tree built. Please create a build \
  directory outside of the source code and call cmake from there. Thank you.")
endif()

if( NOT CMAKE_BUILD_TYPE )
    SET( CMAKE_BUILD_TYPE Debug )
endif()

SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE ) # Ничего не устанавливать

SET( CMAKE_CXX_STANDARD "20")
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++2a -Werror -Wall -Wextra \
  -Wpedantic -Woverloaded-virtual -Winit-self -Wunreachable-code" )
# -Wconversion -Wold-style-cast -Wctor-dtor-privacy -Wnon-virtual-dtor -Weffc++" )
SET( CMAKE_TRY_COMPILE_TARGET_TYPE EXECUTABLE )

if( "_$ENV{CC}" MATCHES "clang" )
  SET( CMAKE_C_COMPILER clang )
  SET( CMAKE_CXX_COMPILER clang++ )
  #SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-PIE" )
  SET( SUFFIX "clang" )
else( "_$ENV{CC}" MATCHES "clang" )
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie" )
  SET( SUFFIX "gcc" )
endif( "_$ENV{CC}" MATCHES "clang" )
SET( APP "${APP}_${SUFFIX}" )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -Wl,-subsystem,windows" )
endif()

find_package( PkgConfig REQUIRED )
pkg_check_modules( GTKMM REQUIRED gtkmm-3.0 )
link_directories( ${GTKMM_LIBRARY_DIRS} )
include_directories( ${GTKMM_INCLUDE_DIRS} )

add_executable( ${APP} "main.cpp" )
target_link_libraries( ${APP} ${GTKMM_LIBRARIES} )

