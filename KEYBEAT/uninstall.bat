@echo off
title KEYBEAT Uninstaller
color 0C

echo.
echo ========================================
echo    🗑️ KEYBEAT UNINSTALLER 🗑️
echo ========================================
echo.
echo WARNING: This will remove KEYBEAT from your system!
echo.

set /p confirm="Are you sure? (Y/N): "
if /i not "%confirm%"=="Y" (
    echo Uninstall cancelled.
    pause
    exit /b
)

echo.
echo [1/3] Removing desktop shortcut...
del "%USERPROFILE%\Desktop\KEYBEAT.lnk" 2>nul
echo ✅ Desktop shortcut removed

echo.
echo [2/3] Removing start menu entry...
del "%APPDATA%\Microsoft\Windows\Start Menu\Programs\KEYBEAT.lnk" 2>nul
echo ✅ Start menu entry removed

echo.
echo [3/3] Removing game files...
rmdir /s /q "%USERPROFILE%\KEYBEAT" 2>nul
echo ✅ Game files removed

echo.
echo ========================================
echo    ✅ KEYBEAT HAS BEEN REMOVED ✅
echo ========================================
echo.
pause
