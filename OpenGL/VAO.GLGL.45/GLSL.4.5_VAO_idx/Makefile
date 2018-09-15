#
# Makefile for 
#  - MINGW32-W64 on MS-Windows MSYS-2
#  - ArchLinux
#

GCC=g++

OS_NAME =$(shell uname)
ifneq (,$(findstring MSYS_NT,$(OS_NAME)))
	D_OS   =-DMINGW64_NT
	SUBSYS =-mwindows -Wl,-subsystem,windows
	SUBLIB =-lmingw32 -lopengl32 -lglfw3
	APPCMD =app.exe
endif

ifneq (,$(findstring Linux,$(OS_NAME)))
	D_OS   =-LINUX
	SUBLIB =-lglfw -lGL -lm
	APPCMD =./app
endif

NAMES    =$(basename $(wildcard *.cpp)) $(basename $(wildcard *.c))
OBJS     =$(patsubst %,obj/%,$(notdir $(subst : , , $(NAMES:=.o))))
CPPFLAGS =$(D_OS) -std=c++14 $(SUBSYS)
LDLIBS   =$(SUBLIB) -lpthread -lpng

all: LINK_APP

LINK_APP: $(OBJS)
	c++ -o app --static $(OBJS) $(LDLIBS)
	$(APPCMD)

obj/%.o: %.cpp
	c++ $(CPPFLAGS) -c $^ -o $@

obj/%.o: %.c
	gcc -c $^ -o $@

clean:
	rm ./obj/*.o $(APPCMD)

.PHONY: all main clean
