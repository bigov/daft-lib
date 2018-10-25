gcc tcpmulticlient.c -DWIN32 -g -lmingw32 -lSDL2main -lSDL2 -lSDL2_net -lws2_32 -lwinmm -o client_c.exe
gcc tcpmultiserver.c -DWIN32 -g -lmingw32 -lSDL2main -lSDL2 -lSDL2_net -lws2_32 -lwinmm -o server_c.exe

