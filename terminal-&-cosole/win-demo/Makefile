#
# Makefile
#

all: win-cpp win-c color trcons

win-cpp:
	$(CC) win-demo.cpp -lncursesw -o win-cpp

win-c:
	$(CC) win-demo.c -lncursesw -o win-c

color:
	$(CC) color-demo.c -lncursesw -o color

trcons:
	$(CC) trcons.cpp -lncursesw -o trcons

.PHONY: all win-cpp win-c color trcons
