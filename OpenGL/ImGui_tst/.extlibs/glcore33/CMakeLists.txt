cmake_minimum_required( VERSION 3.0 )
project( glcore33 )

# MS-Windows MinGW-W64 platform
if   ( (${MINGW}) AND (${CMAKE_SYSTEM_NAME} MATCHES "Windows") )
  SET( LIBS opengl32 )
endif( (${MINGW}) AND (${CMAKE_SYSTEM_NAME} MATCHES "Windows") )

# Linux platform
if   ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
  SET( LIBS GL )
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

ADD_LIBRARY( glcore33 STATIC "gl_core33.c" )
TARGET_LINK_LIBRARIES( glcore33 ${LIBS} )
