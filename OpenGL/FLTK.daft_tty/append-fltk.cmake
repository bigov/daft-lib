#
# Подключение к проекту библиотеки FLTK
#
cmake_minimum_required( VERSION 3.0 )

SET( CXXFLAGS "${CXXFLAGS} -march=x86-64 -mtune=generic -O2 -pipe \
  -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64" )

SET( LDFLAGS "${LDFLAGS} -mwindows -pipe -Wl,--enable-auto-import \
  -Wl,--enable-runtime-pseudo-reloc -lfltk -lole32 -luuid -lcomctl32" )

# Для MS-Windows
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )

  add_compile_definitions(WIN32=1)
  SET( CXXFLAGS "${CXXFLAGS} -mwindows -DWIN32 -DUSE_OPENGL32" )

  SET( LDFLAGS "${LDFLAGS} -mwindows -pipe -Wl,--enable-auto-import \
    -Wl,--enable-runtime-pseudo-reloc -lfltk -lole32 -luuid -lcomctl32" )

  SET( OPTION_USE_XINERAMA OFF CACHE BOOL "FLTK options 0" FORCE )
  SET( OPTION_USE_XFT OFF CACHE BOOL "FLTK options 1" FORCE )
  SET( OPTION_USE_XDBE OFF CACHE BOOL "FLTK options 2" FORCE )
  SET( OPTION_USE_XCURSOR OFF CACHE BOOL "FLTK options 3" FORCE )
  SET( OPTION_USE_XRENDER OFF CACHE BOOL "FLTK options 4" FORCE )
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )

SET( OPTION_BUILD_EXAMPLES OFF CACHE BOOL "No build examples" FORCE )

add_subdirectory( "${FLTK_SRC_DIR}" fltk EXCLUDE_FROM_ALL )

