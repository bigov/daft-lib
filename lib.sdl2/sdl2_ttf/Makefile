# Makefile for showfont

CC = gcc

CFLAGS =-Wl,-subsystem,windows
LIBS   =-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lopengl32 -mwindows

all: showfont glfont

showfont:
	$(CC) -o bin\showfont.exe showfont.c $(CFLAGS) $(LIBS)

glfont:
	$(CC) -o bin\glfont.exe glfont.c $(CFLAGS) $(LIBS)

clean:
	-rm *.o $(EXE)
