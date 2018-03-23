LDLIBS=-L/usr/lib -lSDL2 -lpthread -lSDL2_image -lGL -lm -Og
all: cube
clean:
	rm -f *.o cube
cube: shader_utils.o gl_core_3_0.o
.PHONY: all clean
