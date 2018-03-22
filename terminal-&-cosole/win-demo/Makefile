#
# Makefile for
#

all: win color trcons

win:
	$(CC) win-demo.c -lncursesw -o win-demo

color:
	$(CC) color-demo.c -lncursesw -o color-demo

trcons:
	$(CC) trcons.cpp -lncursesw -o trcons

.PHONY: all win color trcons
