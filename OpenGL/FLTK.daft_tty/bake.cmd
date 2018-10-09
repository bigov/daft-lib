::=======================================::
::       Начальная сборка пакета         ::
::=======================================::
@echo OFF
SETLOCAL
SET "BAKEDIR=_bin_"
IF NOT EXIST "%BAKEDIR%" ( MKDIR "%BAKEDIR%" )
CD "%BAKEDIR%"
cmake ../ -G "MinGW Makefiles" -DOPTION_BUILD_EXAMPLES=0
PAUSE
ENDLOCAL

