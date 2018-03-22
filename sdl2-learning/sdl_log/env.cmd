@ECHO OFF
TITLE Development C (UTF-8)
PUSHD
SETLOCAL
chcp 65001

::SET "PATH=C:\mingw\bin;%PATH%"

ctags -R --c++-kinds=+p --fields=+iaS --extra=+fq

CMD /K

ENDLOCAL
POPD

