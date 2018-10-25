# 
# GNU/Linux or MinGW: is very easy to configure 'make':
# 
# CPPFLAGS=-I/usr/include/SDL2
# LDLIBS=-lSDL2 -lGLEW -lGL
# 
# A little more portable Makefile looks like this:
# 
# CPPFLAGS=$(shell sdl2-config --cflags) $(EXTRA_CPPFLAGS)
# LDLIBS=$(shell sdl2-config --libs) -lGLEW $(EXTRA_LDLIBS)
# EXTRA_LDLIBS?=-lGL
# 

APP=triangle

ifeq ($(OS), Windows_NT)
	CC=i686-w64-mingw32-gcc
	OBJ=obj/win32
	SRC=src
	BIN=$(APP).exe
else
	СС=gcc
	OBJ=./obj/linux
	SRC=./src
	BIN=$(APP)
endif

CPPFLAGS=-I/usr/include/libdrm -I/usr/include/SDL2 -D_REENTRANT
LDLIBS=-L/usr/lib -lGLEW -lSDL2 -lGLU -lGL -lpthread

all: clean linux

linux:
	$(CC) $(CPPFLAGS) -c -o $(OBJ)/$(APP).o $(SRC)/$(APP).c
	$(CC) $(LDLIBS) -o $(BIN) $(OBJ)/$(APP).o
	@./$(BIN)

clean:
	rm -f $(OBJ)/*.o $(BIN)

.PHONY: all clean

