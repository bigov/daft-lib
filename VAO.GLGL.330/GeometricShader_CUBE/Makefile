#
# Makefile for 
#  - MINGW32-W64 on MS-Windows MSYS-2
#

APPCMD =app.exe
#OBJ    =gl_com_4.5.o
OBJ    =gl_core_3_3.o

CPPFLAGS =-std=c++14 --static -fexceptions -Werror -Woverloaded-virtual\
 -Wctor-dtor-privacy -Wnon-virtual-dtor -Weffc++ -Wconversion

LDLIBS =-lmingw32 -lopengl32 -lglfw3 -lgdi32

all: LINK_APP start

LINK_APP: $(OBJ)
	c++ main.cpp $(OBJ) $(CPPFLAGS) $(LDLIBS) -o $(APPCMD)

%.o: %.c
	gcc -c $^ -o $@

start:
	$(APPCMD)

.PHONY: all main
