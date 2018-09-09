#
# Сборка приложения из папки ~BIN:
#
# Под Windows:
# > cmake ../ -G "MinGW Makefiles"
#
# На Linux
# $ cmake ../
#
# Потом (для всех)
# 	cmake --build .
#
# При вызове команды "cmake" НЕОБХОДИМО указать тип сборки:
#
# -DCMAKE_BUILD_TYPE=Debug
# -DCMAKE_BUILD_TYPE=Release
#
# https://cmake.org/Wiki/CMake_Useful_Variables
#
cmake_minimum_required( VERSION 3.0 )	 # Проверка версии CMake.
project( Trickrig )

include_directories( include lib ) # где искать заголовки
SET( CMAKE_VERBOSE_MAKEFILE ON )

if( NOT DEFINED CMAKE_BUILD_TYPE )
	SET( CMAKE_BUILD_TYPE "Debug" )
endif()

if( ${CMAKE_BUILD_TYPE} STREQUAL "Debug" )
	OPTION( WITH_DEBUG_MODE "Build with debug mode" ON )
	SET( EXEC_NAME "app_dbg" )
	SET( WIN_GUI "" )
endif () 
 
if ( ${CMAKE_BUILD_TYPE} STREQUAL "Release" ) 
	OPTION( WITH_DEBUG_MODE "Build with debug mode" OFF )
	SET( EXEC_NAME "app_rel" )
	SET( WIN_GUI "-mwindows -Wl,-subsystem,windows" )
endif () 

SET( MY_FLAGS "-m64 -std=c++14 -fexceptions -Werror -Wpedantic -Wextra\
 -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor -Wall\
 -Wconversion -Winit-self -Wunreachable-code -Weffc++ -Iinclude" )

###
#  Установка параметров для сборки в MinGW-W64 под MS Windows
#
if( (${MINGW}) AND (${CMAKE_SYSTEM_NAME} MATCHES "Windows") )
	SET( CMAKE_CXX_FLAGS "${MY_FLAGS} --static ${WIN_GUI}" )
	SET( LIBS mingw32 opengl32 glfw3 pthread freetype png16 z m gdi32 )
endif( (${MINGW}) AND (${CMAKE_SYSTEM_NAME} MATCHES "Windows") )

###
#  Установка параметров для сборки на Linux
#
if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
SET( CMAKE_CXX_FLAGS "${MY_FLAGS} -I/usr/include/freetype2" )
SET( LIBS glfw GL m pthread freetype png )
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

# список исходников
file( GLOB SRC "src/*.cpp" "lib/gl_core33.c" )

add_executable( ${EXEC_NAME} ${SRC} )
target_link_libraries( ${EXEC_NAME} ${LIBS} )

