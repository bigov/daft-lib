#
# Makefile for 
#  - MINGW32-W64 on MS-Windows MSYS-2
#

APPCMD =app.exe
NAMES =$(basename $(wildcard src/*.cpp)) $(basename $(wildcard deps/*.c))

# список имен объектных файлов
OBJS   =$(patsubst %,obj/%,$(notdir $(subst : , , $(NAMES:=.o))))
CFLAGS =-DMINGW64 -mwindows -Wl,-subsystem,windows -fexceptions -Werror \
 -Wall -Wextra -Wpedantic -Winit-self -Wunreachable-code  \
 -Iinclude -Ideps
CPPFLAGS =-std=c++14 -Woverloaded-virtual -Wctor-dtor-privacy \
 -Wnon-virtual-dtor -Weffc++ -Wconversion -Wold-style-cast -Wsign-conversion \
 $(CFLAGS)

LDLIBS =-lmingw32 -lopengl32 -lglfw3 -lpthread -lfreetype -lpng16 -lz -lm -lgdi32

all: LINK_APP

LINK_APP: $(OBJS)
	c++ -o app --static $(OBJS) $(LDLIBS)

obj/%.o: src/%.cpp
	c++ $(CPPFLAGS) -c $^ -o $@

obj/%.o: deps/%.c
	gcc $(CFLAGS) -c $^ -o $@

clean:
	rm ./obj/*.o $(APPCMD)

.PHONY: all main clean
