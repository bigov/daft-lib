@ECHO OFF
TITLE Development C (UTF-8)
PUSHD
SETLOCAL
chcp 65001

SET "PATH=%PATH%;f:\tools\vim74"

ctags -R --c++-kinds=+p --fields=+iaS --extra=+fq -f tags
::start f:\tools\vim74\gvim.exe

CMD /K

ENDLOCAL
POPD

