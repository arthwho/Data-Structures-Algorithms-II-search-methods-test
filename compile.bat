@echo off

:: Set the output executable name
set output_executable=main
cls

:: Compile the code using gcc and redirect the output to a file
gcc -o %output_executable% .\src\*.c >> output.log 2>&1

:: Check if compilation was successful
if %errorlevel% equ 0 (
  echo Compilation successful. Executable: %output_executable%

)
  