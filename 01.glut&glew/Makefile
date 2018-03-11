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

LDLIBS= -I/usr/include/libdrm -lGLEW -lglut -lGLU -lGL

all: clean linux

linux:
	$(CC) $(LDLIBS) -c -o $(OBJ)/$(APP).o $(SRC)/$(APP).c
	$(CC) $(LDLIBS) -o $(BIN) $(OBJ)/$(APP).o
	
	@./$(BIN)

clean:
	rm -f $(OBJ)/*.o $(BIN)

.PHONY: all clean

