#
# Makefile for 
#  - MINGW32-W64 on MS-Windows MSYS-2
#

APPCMD =app.exe
OBJ    =gl_core_3_3.o

CPPFLAGS =-std=c++14 -fexceptions -Werror -Woverloaded-virtual\
 -Wctor-dtor-privacy -Wnon-virtual-dtor -Weffc++ -Wconversion

LDLIBS =-lmingw32 -lopengl32 -lglfw3 -lgdi32

all: LINK_APP start

LINK_APP: $(OBJ)
	c++ main.cpp tools.cpp $(OBJ) --static $(CPPFLAGS) $(LDLIBS) -o app

%.o: %.c
	gcc -c $^ -o $@
	
start:
	app
#	del *.o *.exe

.PHONY: all main
