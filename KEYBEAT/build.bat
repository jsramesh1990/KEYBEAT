@echo off
title KEYBEAT Build Script
color 0A

echo.
echo ========================================
echo    🎵 KEYBEAT - Build Script 🎵
echo ========================================
echo.
echo [1/4] Checking system requirements...
echo.

REM Check for GCC
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    color 0C
    echo ❌ ERROR: GCC not found!
    echo.
    echo Please install MinGW-w64:
    echo 1. Download from: https://www.mingw-w64.org/
    echo 2. Add to system PATH
    echo.
    pause
    exit /b 1
)
echo ✅ GCC found!

REM Check for source file
if not exist "KEYBEAT.cpp" (
    color 0C
    echo ❌ ERROR: KEYBEAT.cpp not found!
    echo.
    echo Make sure KEYBEAT.cpp is in the current directory.
    echo.
    pause
    exit /b 1
)
echo ✅ Source file found!

echo.
echo [2/4] Cleaning previous builds...
if exist "KEYBEAT.exe" del KEYBEAT.exe
if exist "*.o" del *.o
echo ✅ Clean complete!

echo.
echo [3/4] Compiling KEYBEAT...
echo This may take a moment...

g++ KEYBEAT.cpp -o KEYBEAT.exe -lwinmm -O2 -s -static -Wall

if %errorlevel% neq 0 (
    color 0C
    echo.
    echo ❌ COMPILATION FAILED!
    echo Check for syntax errors in KEYBEAT.cpp
    echo.
    pause
    exit /b 1
)

echo ✅ Compilation successful!

echo.
echo [4/4] Finalizing...
if exist "KEYBEAT.exe" (
    echo ✅ KEYBEAT.exe created!
) else (
    echo ❌ Executable not found!
    pause
    exit /b 1
)

echo.
echo ========================================
echo    🎉 BUILD SUCCESSFUL! 🎉
echo ========================================
echo.
echo File: KEYBEAT.exe
echo Size: 
dir KEYBEAT.exe | find "KEYBEAT.exe"
echo.
echo ========================================
echo To play the game:
echo   1. Double-click KEYBEAT.exe
echo   or
echo   2. Type: KEYBEAT.exe
echo ========================================
echo.
color 0A
echo Press any key to start the game...
pause >nul
KEYBEAT.exe
