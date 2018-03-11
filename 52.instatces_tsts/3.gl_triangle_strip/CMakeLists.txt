#
# Сборка приложения:
#   cmake ../ -G "MinGW Makefiles"

# Потом (для всех)
#   cmake --build .

cmake_minimum_required( VERSION 3.0 )    # Проверка версии CMake.
project( testing )
SET( CMAKE_VERBOSE_MAKEFILE ON )

SET(EXEC_NAME "app" )

SET(3DLIBS "../../../../extlibs/")

# библиотека GLFW3
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE)
SET(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE)
SET(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
SET(GLFW_VULKAN_STATIC OFF CACHE BOOL "Use the Vulkan" FORCE)
add_subdirectory( "${3DLIBS}glfw" "glfw" EXCLUDE_FROM_ALL)

# где искать заголовки
include_directories( "${3DLIBS}glfw/include" "${3DLIBS}glm.old" )
SET( MY_FLAGS "-std=c++14" )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
SET( CMAKE_CXX_FLAGS "${MY_FLAGS} -no-pie" )
SET( LIBS glfw GL)
else()
SET( CMAKE_CXX_FLAGS "${MY_FLAGS} --static" )
SET( LIBS mingw32 opengl32 glfw gdi32 )
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

# список исходников
file( GLOB SRC "*.cpp" "gl_core_3_3.c")

add_executable( ${EXEC_NAME} ${SRC} )
target_link_libraries( ${EXEC_NAME} ${LIBS} )
