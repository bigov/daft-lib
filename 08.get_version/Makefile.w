APP=ver_gl
NCORE=3_3

MINGW = f:\cDev\mingw32\i686-w64-mingw32
CFLAGS = -I$(MINGW)\include\SDL2 -Dmain=SDL_main
LDLIBS = -L$(MINGW)\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lopengl32

all: app 

app:
	gcc -c -o gl_core_$(NCORE).o gl_core_$(NCORE).c
	gcc $(CFLAGS) -c -o $(APP).o $(APP).c
	gcc -o $(APP).exe $(APP).o gl_core_$(NCORE).o $(LDLIBS)
	$(APP).exe

