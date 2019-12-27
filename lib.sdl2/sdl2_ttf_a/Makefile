# Makefile for glfont

CC=c++
CFLAGS=-Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lopengl32 -mwindows

all: glfont

glfont:
	$(CC) -o glfont.exe glfont.cpp $(CFLAGS)

clean:
	-rm *.o $(EXE)
