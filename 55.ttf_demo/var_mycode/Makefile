#----------------------------------------------------------------------------
#
# Makefile for
#
#  - MINGW32-W64 on MS-Windows MSYS-2
#
#----------------------------------------------------------------------------

OBJ =lib/gl_core_3_3.o tools.o

APPCMD =app.exe
STD    =-std=c++14
#--static
LDLIBS =-lmingw32 -lopengl32 -lglfw3 -lfreetype -lpng16 -lz -lgdi32
CLEAR  =rm -rf

CPPFLAGS =$(STD) -fexceptions -Werror -Woverloaded-virtual\
 -Wctor-dtor-privacy -Wnon-virtual-dtor -Weffc++ -Wconversion\
 -I /mingw64/include/freetype2

all: clean link

link: $(OBJ)
	c++ main.cpp $(OBJ) $(CPPFLAGS) $(LDLIBS) -o $(APPCMD)

%.o: %.c
	gcc -c $^ -o $@

%.o: %.cpp
	c++ $(CPPFLAGS) -c $^ -o $@

start:
	$(APPCMD)

clean:
	$(CLEAR) tools.o $(APPCMD)

.PHONY: all link start clean
