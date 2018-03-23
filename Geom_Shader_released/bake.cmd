::
:: ���� ��������� ��ப�:
::
:: clean - ������ ���⪠ � ���ᡮઠ
:: init - ᮧ����� Makefile ��� ᡮન ����୨��
::

@ECHO OFF

IF EXIST CMakeLists.txt (
	MKDIR ~BIN
	COPY /Y /L bake.cmd ~BIN\
	CD ~BIN
	ECHO.
	ECHO ��������! ��� ᡮન �ᯮ���� ����� '~BIN'.
	ECHO.
	CALL bake.cmd
	GOTO _eof
)

IF "%1"=="clean" (
	RD /Q /S CMakeFiles
	DEL /Q *make*.*
	DEL /Q app.exe
)

cmake -DCMAKE_BUILD_TYPE=Debug ..\ -G "MinGW Makefiles"

IF "%1"=="init" GOTO _eof
IF "%2"=="init" GOTO _eof

cmake --build .

IF ERRORLEVEL 1 (
	ECHO ----------------
	ECHO ..�訡�� ᡮન
	ECHO.
	pause
	GOTO _eof
)

CALL app_dbg.exe
IF ERRORLEVEL 1 pause

:_eof
ECHO.
