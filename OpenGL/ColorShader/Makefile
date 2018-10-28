#
# Makefile for 
#  - MINGW32-W64 on MS-Windows MSYS-2
#

APPCMD =app.exe
OBJ    =tools.o

CPPFLAGS =-std=c++17 -fexceptions -Werror -Woverloaded-virtual\
 -Wctor-dtor-privacy -Wnon-virtual-dtor -Weffc++ -Wconversion\
 -Wsign-conversion -mwindows -Wl,-subsystem,windows

LDLIBS =-lepoxy.dll -lglfw3 -lgdi32

all: link start

link: $(OBJ)
	c++ main.cpp $(OBJ) $(CPPFLAGS) $(LDLIBS) -o $(APPCMD)

%.o: %.c
	gcc -c $^ -o $@

%.o: %.cpp
	c++ $(CPPFLAGS) -c $^ -o $@

start:
	$(APPCMD)

clean:
	DEL tools.o $(APPCMD)

.PHONY: all link start clean
