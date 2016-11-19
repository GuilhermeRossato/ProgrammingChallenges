@echo off
cd "F:\2. Projetos\[4 Paralelo] ProgrammingChallenges\ProgrammingChallenges\Solved\Others\BabelsElevator"
mode con lines=8 cols=21
echo.
echo.
echo.
echo       Compiling
F:/TDM-GCC/bin/g++.exe main.cpp -o main.exe -std=c++11 -O3
if NOT ["%errorlevel%"]==["0"] GOTO:SHOWISH
cls
echo.
echo.
echo.
echo         Done
GOTO:EOF
:SHOWISH
mode con lines=30 cols=130
F:/TDM-GCC/bin/g++.exe main.cpp -o main.exe -std=c++11 -O3
pause
