#
# Изучение CMake
#
project(TestApp LANGUAGES CXX)
cmake_minimum_required(VERSION 3.6)

# http://www.openguru.com/2009/04/cmake-detecting-platformoperating.html
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Windows specific code
    set(OperatingSystem "MS Windows")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    set(OperatingSystem "Linux")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# The version number
set(TestApp_VERSION_MAJOR 1)
set(TestApp_VERSION_MINOR 0)

include_directories("f:/cDev/cLibs")
add_subdirectory("src")

set(CMAKE_INSTALL_PREFIX "../bin")
INSTALL(PROGRAMS tmp/src/app.exe DESTINATION ${CMAKE_INSTALL_PREFIX})

