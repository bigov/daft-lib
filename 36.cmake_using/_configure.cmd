::
:: ������ 䠩� ����᪠ �������樨 �஥�� C++.
::

@ECHO OFF
TITLE Development C++
PUSHD
SETLOCAL

SET "DEV=F:\cDev"
SET "M0=i686-6.2.0-release-posix-dwarf-rt_v5-rev0\mingw32"
SET "M1=i686-6.2.0-release-posix-sjlj-rt_v5-rev0\mingw32"
SET "M2=x86_64-6.2.0-release-posix-seh-rt_v5-rev0\mingw64"
SET "M3=x86_64-6.2.0-release-posix-sjlj-rt_v5-rev0\mingw64"

:: �롮� ����室���� ���ᨨ MinGW-W64
SET "MINGW=%DEV%\MinGW\%M1%"
SET "PATH=%DEV%\bin;%MINGW%\bin;%MINGW%\opt\bin;%DEV%\cmake\bin;%PATH%"

ECHO.
ECHO �஢�ઠ:
ECHO =========
ECHO.

IF NOT EXIST tmp (mkdir tmp)
cd tmp

::�������� 䠩��� ᡮન
cmake -G "MinGW Makefiles" ../
IF ERRORLEVEL 1 GOTO _end_batch_

ECHO.
ECHO ���ઠ:
ECHO =======
ECHO.
mingw32-make.exe
IF ERRORLEVEL 1 GOTO _end_batch_
ECHO.
ECHO ��⠭����:
ECHO ==========
ECHO.
mingw32-make.exe install
IF ERRORLEVEL 1 GOTO _end_batch_

ECHO.
cd ..
IF NOT EXIST bin (
ECHO ��� ����� ./bin - ������!
GOTO _end_batch_
)

:: MinGW runtime ������⥪�. (�������� ���ॡ���� ��-� ��)
COPY /B /V /Y /L "%MINGW%\bin\libstdc++-6.dll" bin\
COPY /B /V /Y /L "%MINGW%\bin\libwinpthread-1.dll" bin\
COPY /B /V /Y /L "%MINGW%\bin\libgcc_s_*.dll" bin\

RD /S /Q tmp >nul
:_end_batch_
ENDLOCAL
POPD
ECHO.
pause

