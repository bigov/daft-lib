#
# Для получения сообщений отладки необходимо консольное (ДОС)
# окно. Оно будет каждый раз открываться фоном за окном графического
# приложения. Если его надо скрыть, то в конец строки подключения библиотек
# добавляется параметр -mwindows:
#
# LDLIBS = -L$(MINGW)\lib -lmingw32 -lSDL2main -lSDL2 -lopengl32 -mwindows
#

CC = c++

MINGW = f:\cDev\mingw32\i686-w64-mingw32
INC = -I$(MINGW)\include\SDL2
LIB = -L$(MINGW)\lib

C_FL = -Wl,-subsystem,windows -std=c++11 -c
L_FL = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32
#-mwindows

all: do

do:
	@DEL /Q *.exe
	$(CC) tst0.cpp $(INC) $(C_FL) -o tst0.o
	$(CC) tst0.o $(LIB) $(L_FL) -o t0.exe
	@DEL /Q *.o
	@t0.exe

rm_bin:
	DEL /Q $(APP)

.PHONY: all
