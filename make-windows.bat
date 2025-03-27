@echo off
set CXX=g++
set CXXFLAGS=-std=c++17 -Wall -Iinclude/

set OBJ_DIR=obj
set SRC_DIR=src
set BIN_DIR=bin

:: Create necessary directories
if not exist %OBJ_DIR% mkdir %OBJ_DIR%
if not exist %BIN_DIR% mkdir %BIN_DIR%

:: Compile source files
for %%f in (%SRC_DIR%\*.cc) do (
    set filename=%%~nf
    echo Compiling %%f...
    %CXX% %CXXFLAGS% -c %%f -o %OBJ_DIR%\%%~nf.o
)

:: Link object files
echo Linking...
%CXX% %CXXFLAGS% %OBJ_DIR%\*.o -o %BIN_DIR%\unic.exe

echo Build complete.

:: Clean command
if "%1"=="clean" (
    echo Cleaning...
    rmdir /s /q %OBJ_DIR%
    rmdir /s /q %BIN_DIR%
    echo Clean complete.
)
