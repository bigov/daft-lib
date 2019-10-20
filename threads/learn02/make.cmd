@echo off
@CHCP 65001 > nul
IF EXIST %1.exe DEL %1.exe
c++ -lpthread -Wall -o %1 %1.cpp

IF EXIST %1.exe (call %1.exe) ELSE (
ECHO.
ECHO Что-то пошло не так...
)
