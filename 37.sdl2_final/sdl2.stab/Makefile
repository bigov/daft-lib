#
# Makefile for MS-Windows
#

APP=trick.exe
LIBSPATH=c:/mingw/i686-w64-mingw32/lib

DEFS=-D__MS_WIN__ -DSDL_ASSERT_LEVEL=3 -DSYS_DIR=\"sysdir\"\
	-DWORK_FNAME=\"work.cfg\" -DINI_FNAME=\"ini.cfg\"

CPPFLAGS=$(DEFS) $(INCLUDE) -std=c++11 -mwindows -Wl,-subsystem,windows

L_MINGW =-L$(_MINGW)i686-w64-mingw32\lib -lmingw32 -lopengl32 -lpthread
L_SDL2 =-L$(_SDL2)lib -lSDL2main -lSDL2 -lSDL2_image
LDLIBS=$(L_MINGW) $(L_SDL2)

all: trick start

# список исходных файлов (*.cpp)
LIBS=$(wildcard libs/*/*.cpp) $(wildcard libs/*/mswin/*.cpp)
ALLFN=$(wildcard cpp/*.cpp) $(LIBS)
NAMES=$(ALLFN:.cpp=)
# список объектных файлов, необходимых для сборки
OBJFN=$(NAMES:=.o)

trick: $(OBJFN)

start:
	move $(APP) debug\$(APP)
	call debug\$(APP)

clean:
	@DEL /Q /F cpp\*.o
	@DEL /Q /F libs\rigs\*.o
	@DEL /Q /F libs\gl_load_gen\mswin\*.o

.PHONY: moving start clean
