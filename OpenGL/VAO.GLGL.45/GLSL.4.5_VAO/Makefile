# ---------------------------------------------------------------------------
#
# Makefile for 
#  - MINGW32-W64 on MS-Windows MSYS-2
#
# ---------------------------------------------------------------------------
# список имен исходных файлов (без расширения)
NAMES = $(basename $(wildcard *.cpp)) $(basename $(wildcard *.c))
# список имен объектных файлов
OBJS = $(subst : , , $(NAMES:=.o))

CPPFLAGS=-std=c++14 -fexceptions -Woverloaded-virtual -Wctor-dtor-privacy \
 -Wnon-virtual-dtor -Weffc++ -Wconversion -Wold-style-cast -Wsign-conversion \
 -Werror -Wall -Wextra -Wpedantic -Winit-self -Wunreachable-code

LDLIBS=-lmingw32 -lopengl32 -lglfw3

all: main

main: $(OBJS)
	c++ -o app --static $(OBJS) $(LDLIBS) -mwindows -Wl,-subsystem,windows

%.o: %.cpp
	c++ $(CPPFLAGS) -c $^ -o $@

%.o: %.c
	gcc -c $^ -o $@

.PHONY: all
