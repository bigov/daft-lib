APP=ver_gl
NCORE=3_3

CFLAGS = -I/usr/include/SDL2 -D_REENTRANT
LDLIBS = -L/usr/lib -lSDL2 -lpthread -lSDL2_ttf -lGL

all: app 

app:
	gcc -c -o gl_core_$(NCORE).o gl_core_$(NCORE).c
	gcc $(CFLAGS) -c -o $(APP).o $(APP).c
	gcc -o $(APP) $(APP).o gl_core_$(NCORE).o $(LDLIBS)
	$(APP)
