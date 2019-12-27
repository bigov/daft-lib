APP=simple
CPP=c++
FLAGS=-std=c++14 -lpthread

ifeq ($(OS), Windows_NT)
	BIN=$(APP).exe
	CPPFLAGS=$(FLAGS) -lglfw3
	RM=@IF EXIST $(APP) @DEL $(APP)
else
	BIN=./$(APP)
	CPPFLAGS=$(FLAGS) -ldl -lglfw
	RM=rm -f
endif

all: clean main

main:
	$(CPP) main.cpp glad.c $(CPPFLAGS) -o $(BIN)
	@$(APP)

clean:
	$(RM)

.PHONY: all main cleam
