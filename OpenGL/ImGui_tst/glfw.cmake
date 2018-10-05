
# библиотека GLFW3
SET( GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE )
SET( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE )
SET( GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE )
SET( GLFW_DOCUMENT_INTERNALS OFF CACHE BOOL "Build the GLFW document" FORCE )
SET( GLFW_INSTALL OFF CACHE BOOL "Build the GLFW install" FORCE )
SET( GLFW_USE_MIR OFF CACHE BOOL "Build the GLFW with Mir" FORCE )
SET( GLFW_USE_OSMESA OFF CACHE BOOL "Build the GLFW with os mesa" FORCE )
SET( GLFW_USE_WAYLAND OFF CACHE BOOL "Build the GLFW with Wayland server" FORCE )
SET( GLFW_VULKAN_STATIC OFF CACHE BOOL "Use the Vulkan" FORCE )

include_directories( "${CMAKE_SOURCE_DIR}/../.extlibs/glfw/include" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/../.extlibs/glfw" "glfw" EXCLUDE_FROM_ALL )
