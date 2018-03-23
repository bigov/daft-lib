#----------------------------------------------------------------------------
#
# Makefile for
#
#  - MINGW32-W64 on MS-Windows MSYS-2
#  - Linux native
#
#----------------------------------------------------------------------------

OBJ =lib/gl_core33.o tools.o

ifneq (,$(findstring Linux,$(shell uname)))
        APPCMD =./app
        STD    =-std=c++14
        LDLIBS =-lGL -lglfw -lm -lfreetype -lpng -lz
        CLEAR  =rm -frd
else
        APPCMD =app.exe
        STD    =-std=c++14 --static
        LDLIBS =-lmingw32 -lopengl32 -lglfw3 -lfreetype -lpng16 -lz -lgdi32
        CLEAR  =DEL /Q /S
endif

CPPFLAGS =$(STD) -fexceptions -Werror -Woverloaded-virtual\
 -Wctor-dtor-privacy -Wnon-virtual-dtor -Weffc++ -Wconversion\
 -I/usr/include/freetype2

all: clean link start

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
