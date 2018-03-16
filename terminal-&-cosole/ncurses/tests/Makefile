#
# Makefile for
#

all: bake

bake:
	$(CC) panels-demo.cpp -static -lpanelw -lncursesw -o panels-demo -s
	$(CC) nodelay-input.cpp -static -lncursesw -o nodelay-input -s

.PHONY: all bake
