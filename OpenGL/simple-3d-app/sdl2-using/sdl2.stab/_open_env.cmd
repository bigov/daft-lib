::
:: Пакетный файл для работы над проектом в командной строке
::

@ECHO OFF
PUSHD
SETLOCAL
chcp 65001
TITLE Development C++

SET "_CDEV=F:\cDev\"
SET "_MINGW=%_CDEV%MinGW\i686-6.2.0-release-posix-dwarf-rt_v5-rev0\mingw32\"
SET "_SDL2=%_CDEV%libs\LibSDL\SDL2-2.0.4\i686-w64-mingw32\"
SET "_GLFW=%_CDEV%libs\glfw\glfw-3.2.1.bin.WIN32\"

SET "I_MINGW=-I%_MINGW%i686-w64-mingw32\include\"
SET "I_DEPS=-I%_CDEV%MyProjects\TrickRig\deps\"
SET "INCLUDE=%I_MINGW% %I_DEPS% -Ihpp"

SET "PATH=%_MINGW%bin;%_MINGW%opt\bin;%PATH%"

start f:\tools\vim80\gvim.exe trick.cpp
CMD /K

ENDLOCAL
POPD

