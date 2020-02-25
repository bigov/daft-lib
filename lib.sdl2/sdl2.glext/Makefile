
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

EXTRA_CPPFLAGS=
CPPFLAGS=$(shell sdl2-config --cflags) $(EXTRA_CPPFLAGS)

EXTRA_LDLIBS=-lGLU -lGL
LDLIBS=$(shell sdl2-config --libs) $(EXTRA_LDLIBS)

all: clean linux

linux:
	$(CC) $(CPPFLAGS) -c -o $(OBJ)/$(APP).o $(SRC)/$(APP).c
	$(CC) $(LDLIBS) -o $(BIN) $(OBJ)/$(APP).o
	@./$(BIN)

clean:
	rm -f $(OBJ)/*.o $(BIN)

.PHONY: all clean

