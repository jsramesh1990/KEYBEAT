
# 🎵 KEYBEAT

## *"Every Keystroke Creates a Rhythm Explosion"*

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg" alt="C++17">
  <img src="https://img.shields.io/badge/Platform-Windows-brightgreen.svg" alt="Windows">
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="MIT License">
  <img src="https://img.shields.io/badge/Version-1.0.0-red.svg" alt="Version 1.0.0">
  <img src="https://img.shields.io/badge/Status-Stable-success.svg" alt="Stable">
</p>

---

## 📖 Table of Contents

- [About The Game](#about-the-game)
- [Features](#features)
- [Gameplay Mechanics](#gameplay-mechanics)
- [System Requirements](#system-requirements)
- [Installation & Build Guide](#installation--build-guide)
  - [Windows (MinGW/GCC)](#windows-mingwgcc)
  - [Windows (Visual Studio)](#windows-visual-studio)
  - [Windows (MSVC Command Line)](#windows-msvc-command-line)
  - [Quick Build Script](#quick-build-script)
- [How To Play](#how-to-play)
- [Secret Words List](#secret-words-list)
- [Scoring System](#scoring-system)
- [Controls](#controls)
- [Troubleshooting](#troubleshooting)
- [Customization](#customization)
- [Screenshots](#screenshots)
- [License](#license)
- [Credits](#credits)

---

## 🎮 About The Game

**KEYBEAT** is an innovative, rhythm-based typing reaction game designed for the next generation of gamers and typists. Every keystroke triggers unique visual effects, sounds, and animations — transforming mundane typing into an exciting arcade experience!

**The Core Idea:** Type faster → Build bigger combos → Discover secret words → Become a typing legend!

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🎵 **36+ Unique Reactions** | Every letter (A-Z) and number (0-9) triggers its own special effect |
| 🤫 **Secret Word System** | 10 hidden words unlock massive bonuses and custom animations |
| 🔥 **Combo Streak System** | Type rapidly to multiply your score exponentially |
| 📈 **Level Progression** | Reach score thresholds to level up and earn rewards |
| 🔊 **Dynamic Sound Effects** | Different frequencies for different actions using Windows Beep API |
| 💥 **Particle Effects** | Visual explosions and animations in the console |
| 🏆 **High Score Tracking** | Your best score persists between gaming sessions |
| 🌊 **Screen Shake** | Feel the impact of special moves and mega combos |
| 🎁 **Random Bonus Events** | Surprise rewards keep gameplay exciting |
| 💾 **Save/Load System** | Automatic high score persistence |

---

## 🎯 Gameplay Mechanics

### Rhythm & Timing System
- **Perfect Timing (<300ms between keys)**: +50% score bonus
- **Great Timing (300-600ms)**: +25% score bonus  
- **Good Timing (600-1000ms)**: Standard scoring
- **Slow Timing (>1000ms)**: Breaks combo streak

### Combo Multipliers
| Streak Length | Multiplier | Effect |
|---------------|------------|--------|
| 3-4 | 1.5x | Green glow |
| 5-9 | 2.0x | Yellow + Screen rumble |
| 10-14 | 3.0x | Orange + Sound effect |
| 15+ | 5.0x | RED + EXPLOSION! |

### Level Progression
- **Level 1**: 0-499 points
- **Level 2**: 500-999 points
- **Level 3**: 1000-1999 points
- **Level 4**: 2000-3499 points
- **Level 5**: 3500-4999 points
- **Level 6+**: Every 1500 points

---

## 💻 System Requirements

### Minimum Requirements
| Component | Specification |
|-----------|---------------|
| **OS** | Windows 7, 8, 10, or 11 |
| **CPU** | 1.0 GHz or faster |
| **RAM** | 256 MB |
| **Storage** | 1 MB free space |
| **Sound** | PC Speaker or Audio Output |
| **Display** | 80x25 console resolution |

### Recommended Requirements
| Component | Specification |
|-----------|---------------|
| **OS** | Windows 10/11 |
| **CPU** | 2.0 GHz dual-core |
| **RAM** | 512 MB |
| **Storage** | 5 MB free space |
| **Sound** | Any Windows-compatible audio device |
| **Display** | Fullscreen console mode |

---

## 🔧 Installation & Build Guide

### Prerequisites

Before building, ensure you have one of the following installed:

- **MinGW-w64** (GCC for Windows)
- **Visual Studio** (2017 or later)
- **MSVC Build Tools**

---

### 📥 Windows (MinGW/GCC)

#### Step 1: Install MinGW
1. Download from [mingw-w64.org](http://mingw-w64.org)
2. Run installer and select "x86_64-posix-seh"
3. Add `C:\mingw64\bin` to system PATH

#### Step 2: Verify Installation
```bash
g++ --version
```

#### Step 3: Compile KEYBEAT
```bash
# Navigate to project folder
cd path\to\KEYBEAT

# Compile with sound library
g++ KEYBEAT.cpp -o KEYBEAT.exe -lwinmm -static-libgcc -static-libstdc++

# Or for optimized build
g++ KEYBEAT.cpp -o KEYBEAT.exe -lwinmm -O2 -s -static
```

#### Step 4: Run the Game
```bash
KEYBEAT.exe
```

---

### 🏗️ Windows (Visual Studio)

#### Step 1: Create Project
1. Open Visual Studio
2. File → New → Project
3. Select "Console App (C++)"
4. Name it "KEYBEAT"
5. Click "Create"

#### Step 2: Add Source Code
1. Delete existing `.cpp` file
2. Right-click Source Files → Add → Existing Item
3. Select `KEYBEAT.cpp`

#### Step 3: Configure Linker
1. Right-click project → Properties
2. Linker → Input → Additional Dependencies
3. Add `winmm.lib`
4. Click OK

#### Step 4: Build
- Press `Ctrl+Shift+B` (Build Solution)
- Or Debug → Start Without Debugging (`Ctrl+F5`)

---

### ⚡ Windows (MSVC Command Line)

#### Step 1: Open Developer Command Prompt
- Search "Developer Command Prompt for VS"
- Run as Administrator

#### Step 2: Compile
```bash
cd path\to\KEYBEAT
cl KEYBEAT.cpp /Fe:KEYBEAT.exe /link winmm.lib
```

#### Step 3: Run
```bash
KEYBEAT.exe
```

---

### 🚀 Quick Build Script

Create `build.bat` in your project folder:

```batch
@echo off
echo ========================================
echo    KEYBEAT - Build Script
echo ========================================
echo.

echo [1/3] Checking compiler...
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo ERROR: GCC not found! Please install MinGW.
    pause
    exit /b 1
)

echo [2/3] Compiling KEYBEAT...
g++ KEYBEAT.cpp -o KEYBEAT.exe -lwinmm -O2 -s -static

if %errorlevel% neq 0 (
    echo ERROR: Compilation failed!
    pause
    exit /b 1
)

echo [3/3] Build successful!
echo.
echo ========================================
echo    KEYBEAT.exe has been created!
echo    Run the game by typing: KEYBEAT.exe
echo ========================================
echo.
pause
```

**Run the script:**
```bash
build.bat
```

---

## 🎮 How To Play

### Quick Start Guide

1. **Launch the game** by running `KEYBEAT.exe`
2. **Press ANY key** (A-Z, 0-9, Space) to start
3. **Type rapidly** to build combos
4. **Discover secret words** for massive bonuses
5. **Press ENTER** to check your current word
6. **Press ESC** to save score and exit

### Pro Tips
- 🚀 **Type faster** = Higher multipliers
- 🎵 **Find the rhythm** = Maintain your combo
- 🤫 **Learn secret words** = Maximum points
- ⚡ **Use vowel keys** = Extra 5 points each
- 🔢 **Mix in numbers** = +15 point bonus

---

## 🤫 Secret Words List

Type these words in sequence (press ENTER to trigger):

| Secret Word | Effect | Bonus Points |
|-------------|--------|---------------|
| `boom` | 💥 EXPLOSION animation | 250 |
| `rainbow` | 🌈 Color wave effect | 200 |
| `glitch` | 🌀 Matrix glitch | 300 |
| `dragon` | 🐉 Dragon roar | 350 |
| `magic` | 🎩 Magic trick | 200 |
| `sparkle` | ✨ Sparkle shower | 150 |
| `thunder` | ⚡ Thunder strike | 300 |
| `phoenix` | 🔥 Phoenix rising | 400 |
| `galaxy` | 🌌 Galaxy collapse | 500 |
| `nebula` | 🎨 Nebula paint | 450 |

**Bonus Achievement:** Find all 10 secret words → +1000 points!

---

## 📊 Scoring System

### Base Points
| Action | Points |
|--------|--------|
| Regular letter | 10 × combo multiplier |
| Vowel (A,E,I,O,U) | +5 extra |
| Number (0-9) | +15 extra |
| Space bar | 10 × combo multiplier |

### Bonuses
| Event | Points |
|-------|--------|
| Random bonus (5% chance) | 25-75 |
| Level up | +100 |
| Secret word | 150-500 |
| Perfect rhythm | +50% of base |

### Penalties
| Action | Penalty |
|--------|---------|
| Backspace | -5 points |
| Slow typing | Breaks combo |

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| `A` - `Z` | Type letters (each has unique reaction) |
| `0` - `9` | Type numbers (digit bonus) |
| `SPACE` | Space bar reaction |
| `ENTER` | Check current word for secrets |
| `BACKSPACE` | Delete last character (-5 points) |
| `ESC` | Save and exit game |

---

## 🔧 Troubleshooting

### Common Issues & Solutions

| Problem | Solution |
|---------|----------|
| **"g++ not recognized"** | Install MinGW and add to PATH |
| **No sound effects** | Check if PC speaker is enabled |
| **Game won't compile** | Ensure winmm.lib is linked |
| **Console too small** | Run: `mode con cols=100 lines=45` |
| **Text flickering** | Run in fullscreen mode |
| **High score not saving** | Check write permissions in folder |

### Error Messages

**"LNK1104: cannot open file 'winmm.lib'"**
- Solution: Add `#pragma comment(lib, "winmm.lib")` or link manually

**"Undefined reference to Beep"**
- Solution: Compile with `-lwinmm` flag

---

## 🎨 Customization

### Edit Key Reactions
In `KEYBEAT.cpp`, find `initKeyReactions()`:
```cpp
keyReactions['a'] = "✨ YOUR CUSTOM REACTION ✨";
```

### Add New Secret Words
In `initSecretWords()`:
```cpp
secretWords["yourword"] = {"🎉 MESSAGE 🎉", bonusPoints, "sound", "animation"};
```

### Change Colors
Modify the `ConsoleColor::Color` enum:
```cpp
enum Color {
    YOUR_COLOR = 16,
    // ...
};
```

---

## 📸 Screenshots

```
╔══════════════════════════════════════════╗
║  🎯 KEY PRESSED: 'k' → 🔑 KEY MASTER!    ║
╚══════════════════════════════════════════╝
🔥 5x COMBO! +50 🔥

┌────────────────────────────────────────────┐
│ 📊 STATISTICS                              │
├────────────────────────────────────────────┤
│ 🎯 SCORE: 1250 / 5000 (HIGH)              │
│ ⚡ LEVEL: 3                                │
│ 🔥 COMBO: x5                               │
│ ⌨️  KEYS: 127                              │
│ ⏱️  TIME: 2m 15s                          │
│ 🎁 SECRETS: 2/10                           │
└────────────────────────────────────────────┘

📝 Current Word: "magic"
```

---

## 📜 License

This project is licensed under the **MIT License** - see below:

```
MIT License

Copyright (c) 2024 KEYBEAT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files, to deal in the Software
without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies of the
Software, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
```

---

## 👏 Credits

- **Game Design & Development**: KEYBEAT Team
- **Sound Effects**: Windows Beep API
- **Testing**: Beta testers and typing enthusiasts
- **Inspiration**: Rhythm games and typing tutors

---

## 📞 Support

- **Report Issues**: [GitHub Issues](https://github.com/yourusername/KEYBEAT/issues)
- **Email**: support@keybeat.com
- **Discord**: [Join our server](https://discord.gg/keybeat)

---

## 🌟 Star Us!

If you enjoy **KEYBEAT**, please give us a star on GitHub! ⭐

---

## 🎉 Final Words

> *"Typing has never been this exciting! Every keystroke is a beat, every word is a melody. Find your rhythm, discover secrets, and become a typing legend!"*

**Press any key to start your KEYBEAT journey!** 🎵⌨️💥

---

<p align="center">
  <b>Made with ❤️ for the next generation of typing champions</b><br>
  <b>© 2024 KEYBEAT - All Rights Reserved</b>
</p>
```

---

## 📁 **Additional Files**

### **`build.bat`** (Quick Build Script)

```batch
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
```

---

### **`install.bat`** (Installation Helper)

```batch
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
```

---

### **`uninstall.bat`** (Clean Removal)

```batch
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
```



## 🚀 **Quick Start Commands**

```bash
# Clone or download the project
cd KEYBEAT

# Build the game
build.bat

# Or compile manually
g++ KEYBEAT.cpp -o KEYBEAT.exe -lwinmm

# Play!
KEYBEAT.exe
```

---

**Your KEYBEAT project is now complete with professional documentation and easy build procedures!** 🎵✨
