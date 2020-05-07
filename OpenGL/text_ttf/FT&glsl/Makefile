CPPFLAGS=-I/usr/include/SDL2 -D_REENTRANT -I/usr/include/freetype2
LDLIBS=-lSDL2 -lfreetype -lGL

all: text

clean:
	rm -f *.o text

text: gl_com_4_5.o shader_utils.o

.PHONY: all clean
