@ECHO OFF
ECHO.
SET "EXEC=DEBUG\app.exe"

IF NOT EXIST DEBUG MKDIR DEBUG
IF NOT EXIST obj MKDIR obj
IF EXIST "%EXEC%" DEL /F /Q /S "%EXEC%"

IF "%1"=="clean" GOTO _clean

ECHO Сборка проекта:
ECHO ---------------

mingw32-make.exe -f mswin.make 
IF ERRORLEVEL 1 (
	ECHO ----------------
	ECHO ..ошибка сборки.
	ECHO.
	pause
	GOTO _eof
)

MOVE /Y app.exe DEBUG\
CD DEBUG
CALL app.exe
IF ERRORLEVEL 1 pause
CD ..
GOTO _eof

:_clean
ECHO Очистка данных:
ECHO ---------------
DEL /F /Q /S "obj\*"

:_eof
ECHO.

