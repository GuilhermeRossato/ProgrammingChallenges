@echo off
cls
:ask
echo [C] Compile
echo [R] Run
echo [L] Load Input
echo [S] Save Output
echo [M] Many Loads
set INPUT=
set /P INPUT=%=%
if /I %INPUT%==C goto compile
if /I %INPUT%==R goto run
if /I %INPUT%==L goto loadrun
if /I %INPUT%==S goto saverun
if /I %INPUT%==M goto manyload
goto EOF
:compile
cls
"F:\1. Programas\Java\jdk1.6.0_21\bin\javac.exe" Main.java -g
echo Compiled
echo ---------------------------------------
goto ask
:run
cls
"F:\1. Programas\Java\jdk1.6.0_21\bin\java.exe" Main
echo ---------------------------------------
goto ask
:loadrun
cls
"F:\1. Programas\Java\jdk1.6.0_21\bin\java.exe" Main < input.txt
echo ---------------------------------------
goto ask
:saverun
cls
"F:\1. Programas\Java\jdk1.6.0_21\bin\java.exe" Main > output.txt
echo ---------------------------------------
goto ask
:manyload
cls
set NUM=0
:loop
echo Reading "/Input/file%NUM%.txt"
if %NUM%==99 goto endloop
"F:\1. Programas\Java\jdk1.6.0_21\bin\java.exe" Main < "Input/file%NUM%.txt"
set /a NUM=(%NUM%+1)
goto loop
:endloop
echo ---------------------------------------
goto ask