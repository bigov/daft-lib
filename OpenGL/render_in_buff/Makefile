<<<<<<< HEAD:OpenGL/complete_simple/Makefile
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
=======
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
	$(CPP) main.cpp glad/glad.c $(CPPFLAGS) -o $(BIN)
	$(RUN_APP)

clean:
	$(RM)

.PHONY: all main cleam
>>>>>>> ba964a66419c63ab368d123aa3f2a9a170435aa6:OpenGL/render_in_buff/Makefile
