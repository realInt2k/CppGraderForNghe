@echo off
setlocal

rem Get the first argument as the cpp file
set "cpp_file=%1"

rem Compile the grader.cpp file
g++ grader.cpp -o grader
if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)

rem Run the compiled grader with the provided cpp file
grader.exe %cpp_file%

endlocal