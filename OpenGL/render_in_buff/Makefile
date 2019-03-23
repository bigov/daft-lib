APP=simple
CPP=c++
FLAGS=-std=c++14 -lpthread

ifeq ($(OS), Windows_NT)
	BIN=$(APP).exe
	CPPFLAGS=$(FLAGS) -lglfw3
	RM=@IF EXIST $(APP) @DEL $(APP)
	RUN_APP=$(APP)
else
	BIN=./$(APP)
	CPPFLAGS=$(FLAGS) -ldl -lglfw
	RM=if [ -e ./$(APP) ]; then rm ./$(APP); fi
	RUN_APP=./$(APP)
endif

all: clean main

main:
	$(CPP) main.cpp glad.c $(CPPFLAGS) -o $(BIN)
	$(RUN_APP)

clean:
	$(RM)

.PHONY: all main cleam
