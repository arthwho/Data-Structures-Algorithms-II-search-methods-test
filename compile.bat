@echo off

:: Set the output executable name
set output_executable=main

:: Compile the code using gcc
gcc -o %output_executable% .\src\*.c 

:: Check if compilation was successful
if %errorlevel% equ 0 (
  cls
  echo Compilation successful. Executable: %output_executable%
)