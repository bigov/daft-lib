#
# Изучение CMake
#
cmake_minimum_required(VERSION 3.6)
project(TestApp LANGUAGES CXX)

# исходники
#set(SOURCE app.cpp)
#set(HEADER glm/glm.hpp glm/gtc/constants.hpp)

# необходимый результат
add_executable(app main.cpp) # Создает исполняемый файл из исходника

