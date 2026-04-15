@echo off
title KEYBEAT Installer
color 0B

echo.
echo ========================================
echo    🎵 KEYBEAT INSTALLER 🎵
echo ========================================
echo.

REM Create installation directory
set INSTALL_DIR=%USERPROFILE%\KEYBEAT

echo [1/5] Creating installation folder...
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"
echo ✅ Created: %INSTALL_DIR%

echo.
echo [2/5] Copying game files...
copy "KEYBEAT.cpp" "%INSTALL_DIR%\" >nul
copy "KEYBEAT.exe" "%INSTALL_DIR%\" >nul 2>nul
echo ✅ Files copied!

echo.
echo [3/5] Creating desktop shortcut...
powershell -Command "$WS = New-Object -ComObject WScript.Shell; $SC = $WS.CreateShortcut('%USERPROFILE%\Desktop\KEYBEAT.lnk'); $SC.TargetPath = '%INSTALL_DIR%\KEYBEAT.exe'; $SC.Save()"
echo ✅ Shortcut created on Desktop!

echo.
echo [4/5] Creating start menu entry...
powershell -Command "$WS = New-Object -ComObject WScript.Shell; $SC = $WS.CreateShortcut('%APPDATA%\Microsoft\Windows\Start Menu\Programs\KEYBEAT.lnk'); $SC.TargetPath = '%INSTALL_DIR%\KEYBEAT.exe'; $SC.Save()"
echo ✅ Start menu entry created!

echo.
echo [5/5] Installation complete!
echo.
echo ========================================
echo    🎉 KEYBEAT IS NOW INSTALLED! 🎉
echo ========================================
echo.
echo Installation Location: %INSTALL_DIR%
echo.
echo To play:
echo   • Desktop shortcut added
echo   • Start Menu shortcut added
echo   • Run: %INSTALL_DIR%\KEYBEAT.exe
echo.
echo ========================================
pause
