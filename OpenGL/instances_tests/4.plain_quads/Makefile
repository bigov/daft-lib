#
# Makefile for
#  - MINGW32-W64 on MS-Windows MSYS-2
#

OBJ    =gl_core_3_3.o tools.o

OS_NAME =$(shell uname)

ifneq (,$(findstring Linux,$(OS_NAME)))
	APPNAME =app
	APPCMD  =./app
	STD     =-std=c++14
	LDLIBS  =-lGL -lglfw -lm
	CLEAR   =rm -frd
else
	APPNAME =app.exe
	APPCMD  =app.exe
	STD     =-std=c++14 --static
	LDLIBS  =-lmingw32 -lopengl32 -lglfw3 -lgdi32 -I"../../../../extlibs/glm"
	CLEAR   =DEL /Q /S
endif

CPPFLAGS =$(STD)

all: clean link start

link: $(OBJ)
	c++ main.cpp $(OBJ) $(CPPFLAGS) $(LDLIBS) -o $(APPNAME)

%.o: %.c
	gcc -c $^ -o $@

%.o: %.cpp
	c++ $(CPPFLAGS) -c $^ -o $@

start:
	$(APPCMD)

clean:
	$(CLEAR) *.o $(APPNAME)

.PHONY: all link start clean
