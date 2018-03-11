#
# Makefile for MINGW32-W64 on MS-Windows MSYS-2
#

GCC=g++

INCLUDE =-Iinclude -Ideps -I~/cDev/_DEPS_

OS_NAME =$(shell uname)
ifneq (,$(findstring MINGW64_NT,$(OS_NAME)))
	D_OS =-DMINGW64_NT
endif

NAMES =$(basename $(wildcard src/*.cpp)) $(basename $(wildcard src/*.c))
DEPS  =$(wildcard deps/*.cpp)

# список имен объектных файлов
OBJS  =$(patsubst %,obj/%,$(notdir $(subst : , , $(NAMES:=.o)))) \
	$(DEPS:.cpp=.o)
CPPFLAGS =$(D_OS) $(INCLUDE) -std=c++14 -mwindows
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lfreetype -mwindows
all: LINK_APP

LINK_APP: $(OBJS)
	c++ $(OBJS) $(LDLIBS) -o app
	./app.exe

obj/%.o: src/%.cpp
	c++ $(CPPFLAGS) -c $^ -o $@

deps/%.o: deps/%.cpp
	c++ $(CPPFLAGS) -c $^ -o $@

clean:
	rm obj/*.o app.exe

.PHONY: all main clean
