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

APP=demowin

СС=gcc
BIN=$(APP)

CPPFLAGS=-I/usr/include/libdrm -I/usr/include/SDL2 -D_REENTRANT
LDLIBS=-L/usr/lib -lGLEW -lSDL2 -lGLU -lGL -lpthread

all: linux

linux:
	$(CC) $(CPPFLAGS) -c -o $(APP).o $(APP).c
	$(CC) $(LDLIBS) -o $(BIN) $(APP).o

	@./$(BIN)

clean:
	rm -f $(OBJ)/*.o $(BIN)

.PHONY: all clean

