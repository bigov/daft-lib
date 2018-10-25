#!/bin/bash --

c++ -L/usr/lib -lSDL2 -lpthread -lGL -lm -I/usr/include/SDL2 \
	-D_REENTRANT -Wall -o syswm syswm.cpp

echo ''
echo '---'
./syswm
echo '---'
echo ''

