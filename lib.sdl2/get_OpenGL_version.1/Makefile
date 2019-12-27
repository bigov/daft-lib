APP=gl_ver_test
CC=c++

exec_prefix=c:\mingw\i686-w64-mingw32

#dynamic link
#LDLIBS =-lopengl32
#SDLLIBS=-L$(exec_prefix)\lib -lmingw32 -lSDL2main -lSDL2 -mwindows

#static link
CPPFLAGS =-L$(exec_prefix)\lib -lmingw32 -lSDL2main -lSDL2  -mwindows \
		-Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 \
		-lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion \
		-luuid -static-libgcc
LDLIBS =-lopengl32 -static

all: gl_ver_test

run:
	$(APP).exe

