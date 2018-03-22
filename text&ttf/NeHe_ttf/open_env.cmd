::
:: Пакетный файл для окружения MSYS2
::

@ECHO OFF
PUSHD
SETLOCAL
chcp 65001
TITLE Development MSYS2 C++
SET "PATH=S:\mingw64\bin;S:\usr\bin;%PATH%"

CALL make_tags.cmd
START f:\tools\vim80\gvim.exe src\main.cpp

CMD /K

ENDLOCAL
POPD

