#
# Makefile for MINGW32-W64 on MS-Windows MSYS-2
#

GCC=g++

INCLUDE =-Iinclude -I~/cDev/_DEPS_

OS_NAME =$(shell uname)
ifneq (,$(findstring MINGW64_NT,$(OS_NAME)))
	D_OS =-DMINGW64_NT
endif

# список имен исходных файлов
#SRC =$(wildcard src/*.cpp) $(wildcard src/*.c)

NAMES =$(basename $(wildcard src/*.cpp)) $(basename $(wildcard src/*.c))
# список имен объектных файлов
OBJS  =$(patsubst %,obj/%,$(notdir $(subst : , , $(NAMES:=.o))))

CPPFLAGS =$(D_OS) $(INCLUDE) -std=c++14 -mwindows -Wl,-subsystem,windows
LDLIBS   =-lmingw32 -lopengl32 -lpthread -lSDL2main -lSDL2
#VPATH = ./src:

all: LINK_APP

LINK_APP: $(OBJS)
	c++ -o app $(OBJS) $(LDLIBS)
	./app.exe

obj/%.o: src/%.cpp
	c++ $(CPPFLAGS) -c $^ -o $@

clean:
	rm ./obj/*.o ./app.exe

.PHONY: all main clean
