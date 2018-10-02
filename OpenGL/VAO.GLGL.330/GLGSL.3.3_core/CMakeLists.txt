cmake_minimum_required( VERSION 3.0 )

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Исходные и подключаемые файлы
SET( APP_SRC_FILES
  "${CMAKE_SOURCE_DIR}/main.cpp"
)

# папка библиотек
SET( LIB_DIR "d:/dev/libs" )

# Компилируемые библиотеки
# ------------------------
# GlLoadLib
SET( INC_DIRS "${LIB_DIR}/glcore33" )
add_subdirectory( "${LIB_DIR}/glcore33" "glcore33" EXCLUDE_FROM_ALL)

# GLFW3
SET( INC_DIRS "${INC_DIRS}" "${LIB_DIR}/glfw/include" )
add_subdirectory( "${LIB_DIR}/glfw" "glfw" EXCLUDE_FROM_ALL)

include_directories("${INC_DIRS}")
add_executable( app ${APP_SRC_FILES} )
target_link_libraries( app mingw32 glcore33 glfw gdi32 )

