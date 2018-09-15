#
# Makefile for MS-Windows
#

APP=app.exe
LIBSPATH=c:/mingw/i686-w64-mingw32/lib

DEFS=-D__MS_WIN__ -DSDL_ASSERT_LEVEL=3 -DSYS_DIR=\"sysdir\"\
	-DWORK_FNAME=\"work.cfg\" -DINI_FNAME=\"ini.cfg\" $(INCLUDE)

CPPFLAGS=$(DEFS) -Iinclude -std=c++11 -mwindows -Wl,-subsystem,windows

L_MINGW =-L$(_MINGW)i686-w64-mingw32\lib -lmingw32 -lopengl32 -lpthread
L_SDL2 =-L$(_SDL2)lib -lSDL2main -lSDL2 -lSDL2_image
LDLIBS=$(L_MINGW) $(L_SDL2)

all: app start

# список исходных файлов (*.cpp)
ALLFN=$(wildcard src/*.cpp)
NAMES=$(ALLFN:.cpp=)
# список объектных файлов, необходимых для сборки
OBJFN=$(NAMES:=.o)

app: $(OBJFN)

start:
	move $(APP) debug\$(APP)
	call debug\$(APP)

clean:
	@DEL /Q /F src\*.o

.PHONY: moving start clean
