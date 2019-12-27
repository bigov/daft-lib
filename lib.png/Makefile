#
# Makefile for MINGW32-W64 on MS-Windows MSYS-2
#

GCC=g++

NAMES =$(basename $(wildcard src/*.cpp))
OBJS  =$(patsubst %,obj/%,$(notdir $(subst : , , $(NAMES:=.o)))) 
	
CFLAGS   =-mwindows -Wl,-subsystem,windows
CPPFLAGS =$(CFLAGS) -std=c++14
LDLIBS   =-lmingw32 -lz -lpng

all: LINK_APP

LINK_APP: $(OBJS)
	c++ $(OBJS) $(LDLIBS) -o app.exe
	./app.exe

obj/%.o: src/%.cpp
	c++ $(CPPFLAGS) -c $^ -o $@

clean:
	rm obj/*.o app.exe

.PHONY: all main clean
