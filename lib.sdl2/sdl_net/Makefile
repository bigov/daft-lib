GCC=g++
FLAGS= -std=c++11
#-mwindows -Wl,-subsystem,windows
#CFLAGS=-g -O2 -Wall $(shell sdl2-config --cflags)
#LDFLAGS=-g -O2 -Wall 
LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_net
#-lSDL2_image -lSDL2_ttf -lopengl32 -lpthread 
# for MS-Windows need:
# -lmingw32

all: clean server

server:
	g++ $(FLAGS) -c tcputil.cpp
	g++ $(FLAGS) tcpmultiserver.cpp tcputil.o $(LIBS) -o server

clean:
	del *.o
	del server.exe

