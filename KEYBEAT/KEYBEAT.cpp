//=============================================================================
// TYPE REACTOR 3000 - Ultimate Typing Reaction Game
//=============================================================================
// A playful, interactive typing game where every keypress triggers
// unique visual, audio, and haptic feedback reactions!
//
// Features:
// • 36+ unique key reactions (A-Z, 0-9, Space)
// • 10+ secret words with custom animations
// • Combo streak system with speed detection
// • Dynamic sound effects (Windows Beep API)
// • Particle effects in console
// • Screen shake and color animations
// • Score tracking with high score persistence
// • Level progression system
//=============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>
#include <conio.h>      // For _kbhit(), _getch()
#include <windows.h>    // For Beep(), SetConsoleTextAttribute()
#include <mmsystem.h>   // For PlaySound()

#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace chrono;

//=============================================================================
// COLOR MANAGEMENT CLASS
//=============================================================================
class ConsoleColor {
private:
    HANDLE hConsole;
    
public:
    enum Color {
        BLACK = 0,
        DARK_BLUE = 1,
        DARK_GREEN = 2,
        DARK_CYAN = 3,
        DARK_RED = 4,
        DARK_MAGENTA = 5,
        DARK_YELLOW = 6,
        LIGHT_GRAY = 7,
        DARK_GRAY = 8,
        BLUE = 9,
        GREEN = 10,
        CYAN = 11,
        RED = 12,
        MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15
    };
    
    ConsoleColor() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    
    void set(Color color) {
        SetConsoleTextAttribute(hConsole, color);
    }
    
    void reset() {
        SetConsoleTextAttribute(hConsole, WHITE);
    }
    
    void setBright(Color color) {
        SetConsoleTextAttribute(hConsole, color | FOREGROUND_INTENSITY);
    }
};

//=============================================================================
// PARTICLE SYSTEM FOR CONSOLE
//=============================================================================
struct Particle {
    int x, y;
    char symbol;
    int life;
    int speedX, speedY;
};

class ParticleSystem {
private:
    vector<Particle> particles;
    int consoleWidth;
    
public:
    ParticleSystem() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        consoleWidth = csbi.dwSize.X;
    }
    
    void addExplosion(int centerX, int centerY, char symbol) {
        for(int i = 0; i < 20; i++) {
            Particle p;
            p.x = centerX + (rand() % 40 - 20);
            p.y = centerY + (rand() % 10 - 5);
            p.symbol = symbol;
            p.life = 10 + (rand() % 20);
            p.speedX = rand() % 5 - 2;
            p.speedY = rand() % 3 - 1;
            particles.push_back(p);
        }
    }
    
    void update() {
        for(auto it = particles.begin(); it != particles.end();) {
            it->life--;
            it->x += it->speedX;
            it->y += it->speedY;
            
            if(it->life <= 0 || it->x < 0 || it->x > consoleWidth) {
                it = particles.erase(it);
            } else {
                ++it;
            }
        }
    }
    
    void draw() {
        for(const auto& p : particles) {
            COORD coord = {static_cast<SHORT>(p.x), static_cast<SHORT>(p.y)};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout << p.symbol;
        }
    }
};

//=============================================================================
// MAIN GAME CLASS
//=============================================================================
class TypeReactor3000 {
private:
    // Game State Variables
    int score;
    int highScore;
    int level;
    int streak;
    int totalKeys;
    int comboMultiplier;
    int secretWordsFound;
    
    // Timing Variables
    steady_clock::time_point lastKeyTime;
    steady_clock::time_point gameStartTime;
    
    // Input Buffer
    string currentWord;
    
    // Reaction Maps
    map<char, string> keyReactions;
    map<string, ReactionEffect> secretWords;
    
    // Systems
    ConsoleColor color;
    ParticleSystem particles;
    
    //=========================================================================
    // STRUCT FOR SECRET WORD EFFECTS
    //=========================================================================
    struct ReactionEffect {
        string message;
        int bonusPoints;
        string soundType;
        string animation;
    };
    
public:
    //=========================================================================
    // CONSTRUCTOR - Initializes all game systems
    //=========================================================================
    TypeReactor3000() : score(0), level(1), streak(0), totalKeys(0), 
                        comboMultiplier(1), secretWordsFound(0) {
        srand(time(nullptr));
        loadHighScore();
        initKeyReactions();
        initSecretWords();
        lastKeyTime = steady_clock::now();
        gameStartTime = steady_clock::now();
    }
    
    //=========================================================================
    // INITIALIZE ALL KEY REACTIONS (A-Z, 0-9, SPACE)
    //=========================================================================
    void initKeyReactions() {
        // Letters A-M
        keyReactions['a'] = "✨ SPARKLE SHOWER! ✨";
        keyReactions['b'] = "🦋 BUTTERFLY SWARM! 🦋";
        keyReactions['c'] = "🐱 CAT CHOIR: MEOW! 🐱";
        keyReactions['d'] = "💃 DANCE EXPLOSION! 💃";
        keyReactions['e'] = "⚡ ELECTRIC SURGE! ⚡";
        keyReactions['f'] = "🔥 DRAGON FIRE! 🔥";
        keyReactions['g'] = "🎮 GAME POWER-UP! 🎮";
        keyReactions['h'] = "❤️ HEART RAIN! ❤️";
        keyReactions['i'] = "🍦 ICE CREAM PARTY! 🍦";
        keyReactions['j'] = "🤡 JOKER LAUGHTER! 🤡";
        keyReactions['k'] = "🔑 KEY MASTER! 🔑";
        keyReactions['l'] = "🌈 LASER LIGHT SHOW! 🌈";
        keyReactions['m'] = "🌙 MOON JUMP! 🌙";
        
        // Letters N-Z
        keyReactions['n'] = "🎵 MUSIC NOTE STORM! 🎵";
        keyReactions['o'] = "🌀 ORBIT SPIN! 🌀";
        keyReactions['p'] = "🎉 PARTY POPPERS! 🎉";
        keyReactions['q'] = "❓ MYSTERY MAGIC! ❓";
        keyReactions['r'] = "🤖 ROBOT INVASION! 🤖";
        keyReactions['s'] = "⭐ SUPERNOVA BLAST! ⭐";
        keyReactions['t'] = "🚀 ROCKET LAUNCH! 🚀";
        keyReactions['u'] = "☂️ UMBRELLA FLOAT! ☂️";
        keyReactions['v'] = "🎻 VIOLIN VIBES! 🎻";
        keyReactions['w'] = "🌊 TSUNAMI WAVE! 🌊";
        keyReactions['x'] = "❌ X-RAY VISION! ❌";
        keyReactions['y'] = "💛 YELLOW YOYO! 💛";
        keyReactions['z'] = "⚡ ZAP ZAP ZAP! ⚡";
        
        // Numbers
        keyReactions['0'] = "🔴 ZERO HERO! 🔴";
        keyReactions['1'] = "🟡 ONE HIT WONDER! 🟡";
        keyReactions['2'] = "🔵 DOUBLE DRAGON! 🔵";
        keyReactions['3'] = "🟣 TRIPLE TROUBLE! 🟣";
        keyReactions['4'] = "🟢 FOUR WINDS! 🟢";
        keyReactions['5'] = "🟠 FIVE STAR GENERAL! 🟠";
        keyReactions['6'] = "📀 SIX PACK POWER! 📀";
        keyReactions['7'] = "🌈 SEVEN RAINBOWS! 🌈";
        keyReactions['8'] = "🐙 OCTOPUS ATTACK! 🐙";
        keyReactions['9'] = "🌙 NINE LIVES! 🌙";
        
        // Special Keys
        keyReactions[' '] = "🕊️ SPACE TIME WARP! 🕊️";
        keyReactions['\t'] = "↹ TAB JUMP! ↹";
    }
    
    //=========================================================================
    // INITIALIZE SECRET WORDS WITH SPECIAL EFFECTS
    //=========================================================================
    void initSecretWords() {
        ReactionEffect boom = {"💥 MEGA EXPLOSION! 💥", 250, "explosion", "boom"};
        ReactionEffect rainbow = {"🌈 COLOR WAVE! 🌈", 200, "magic", "rainbow"};
        ReactionEffect glitch = {"🌀 MATRIX GLITCH! 🌀", 300, "glitch", "glitch"};
        ReactionEffect dragon = {"🐉 DRAGON AWAKENS! 🐉", 350, "roar", "dragon"};
        ReactionEffect magic = {"🎩 MAGIC TRICK! 🎩", 200, "sparkle", "magic"};
        ReactionEffect sparkle = {"✨ MAXIMUM SPARKLE! ✨", 150, "sparkle", "sparkle"};
        ReactionEffect thunder = {"⚡ THUNDER STRIKE! ⚡", 300, "thunder", "thunder"};
        ReactionEffect phoenix = {"🔥 PHOENIX RISING! 🔥", 400, "fire", "phoenix"};
        ReactionEffect galaxy = {"🌌 GALAXY COLLAPSE! 🌌", 500, "cosmic", "galaxy"};
        ReactionEffect nebula = {"🎨 NEBULA PAINT! 🎨", 450, "art", "nebula"};
        
        secretWords["boom"] = boom;
        secretWords["rainbow"] = rainbow;
        secretWords["glitch"] = glitch;
        secretWords["dragon"] = dragon;
        secretWords["magic"] = magic;
        secretWords["sparkle"] = sparkle;
        secretWords["thunder"] = thunder;
        secretWords["phoenix"] = phoenix;
        secretWords["galaxy"] = galaxy;
        secretWords["nebula"] = nebula;
    }
    
    //=========================================================================
    // LOAD HIGH SCORE FROM FILE
    //=========================================================================
    void loadHighScore() {
        ifstream file("highscore.dat");
        if(file.is_open()) {
            file >> highScore;
            file.close();
        } else {
            highScore = 0;
        }
    }
    
    //=========================================================================
    // SAVE HIGH SCORE TO FILE
    //=========================================================================
    void saveHighScore() {
        if(score > highScore) {
            highScore = score;
            ofstream file("highscore.dat");
            if(file.is_open()) {
                file << highScore;
                file.close();
            }
        }
    }
    
    //=========================================================================
    // PLAY SOUND EFFECTS BASED ON TYPE
    //=========================================================================
    void playSound(const string& soundType) {
        if(soundType == "explosion") {
            Beep(200, 100);
            Beep(150, 100);
            Beep(100, 200);
        } 
        else if(soundType == "magic") {
            Beep(523, 150);
            Beep(659, 150);
            Beep(784, 300);
        }
        else if(soundType == "glitch") {
            Beep(440, 50);
            Beep(880, 50);
            Beep(440, 50);
            Beep(220, 100);
        }
        else if(soundType == "roar") {
            Beep(100, 200);
            Beep(80, 300);
            Beep(60, 400);
        }
        else if(soundType == "thunder") {
            Beep(60, 500);
            Beep(100, 200);
        }
        else if(soundType == "fire") {
            Beep(300, 100);
            Beep(400, 100);
            Beep(500, 150);
        }
        else if(soundType == "cosmic") {
            Beep(880, 200);
            Beep(1760, 200);
            Beep(880, 400);
        }
        else if(soundType == "sparkle") {
            Beep(1047, 80);
            Beep(1175, 80);
            Beep(1319, 160);
        }
        else {
            // Default key sound
            Beep(700, 50);
        }
    }
    
    //=========================================================================
    // ANIMATION EFFECTS
    //=========================================================================
    void playAnimation(const string& animation) {
        if(animation == "boom") {
            for(int i = 0; i < 3; i++) {
                color.set(ConsoleColor::RED);
                cout << "💥 BOOM! 💥\r";
                this_thread::sleep_for(milliseconds(100));
                color.set(ConsoleColor::YELLOW);
                cout << "💥 BOOM! 💥\r";
                this_thread::sleep_for(milliseconds(100));
            }
            cout << "              \r";
        }
        else if(animation == "rainbow") {
            ConsoleColor::Color colors[] = {
                ConsoleColor::RED, ConsoleColor::YELLOW, 
                ConsoleColor::GREEN, ConsoleColor::CYAN, 
                ConsoleColor::BLUE, ConsoleColor::MAGENTA
            };
            for(int i = 0; i < 60; i++) {
                color.set(colors[i % 6]);
                cout << "🌈";
                this_thread::sleep_for(milliseconds(20));
            }
            cout << "\n";
        }
        else if(animation == "glitch") {
            for(int i = 0; i < 10; i++) {
                color.set(ConsoleColor::GREEN);
                cout << "01001110 01100101 01110101 01110010 01101111\n";
                this_thread::sleep_for(milliseconds(50));
                color.set(ConsoleColor::CYAN);
                cout << "01100111 01101100 01101001 01110100 01100011 01101000\n";
                this_thread::sleep_for(milliseconds(50));
            }
        }
        else if(animation == "dragon") {
            color.set(ConsoleColor::RED);
            cout << R"(
                      )\\      )\\
                     /  \\    / _\\   🐉
                    |\\_/|  |/   \\  
                    |   |__/|   |  
                   /      \\ |   |  
                  |   🔥   )/   /   
                   \\     _/   /    
                    `---`    \\    
            )";
            this_thread::sleep_for(milliseconds(500));
        }
        else if(animation == "sparkle") {
            for(int i = 0; i < 20; i++) {
                color.set(ConsoleColor::YELLOW);
                cout << "✨";
                this_thread::sleep_for(milliseconds(30));
                color.set(ConsoleColor::WHITE);
                cout << "  ";
                this_thread::sleep_for(milliseconds(30));
            }
            cout << "\n";
        }
        else if(animation == "phoenix") {
            color.set(ConsoleColor::MAGENTA);
            cout << "🔥🔥🔥 PHOENIX RISING 🔥🔥🔥\n";
            this_thread::sleep_for(milliseconds(300));
            color.set(ConsoleColor::RED);
            cout << "╔══════════════════════════╗\n";
            cout << "║    BIRD OF FLAME ASCENDS ║\n";
            cout << "╚══════════════════════════╝\n";
        }
        else if(animation == "galaxy") {
            for(int i = 0; i < 3; i++) {
                color.set(ConsoleColor::BLUE);
                cout << "🌌";
                this_thread::sleep_for(milliseconds(100));
                color.set(ConsoleColor::MAGENTA);
                cout << "⭐";
                this_thread::sleep_for(milliseconds(100));
                color.set(ConsoleColor::CYAN);
                cout << "🌠";
                this_thread::sleep_for(milliseconds(100));
            }
            cout << "\n";
        }
        color.reset();
    }
    
    //=========================================================================
    // SCREEN SHAKE EFFECT
    //=========================================================================
    void shakeScreen() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        
        for(int shake = 0; shake < 5; shake++) {
            COORD newPos = {static_cast<SHORT>(rand() % 5 - 2), csbi.dwCursorPosition.Y};
            SetConsoleCursorPosition(hConsole, newPos);
            this_thread::sleep_for(milliseconds(20));
        }
        
        SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
    }
    
    //=========================================================================
    // CHECK AND UPDATE COMBO STREAK
    //=========================================================================
    void updateCombo() {
        auto now = steady_clock::now();
        auto elapsed = duration_cast<milliseconds>(now - lastKeyTime).count();
        
        if(elapsed < 400) { // Fast typing
            streak++;
            comboMultiplier = 1 + (streak / 5);
            
            if(streak >= 3 && streak < 5) {
                color.set(ConsoleColor::GREEN);
                cout << "🔥 " << streak << "x COMBO! +" << (10 * comboMultiplier) << " 🔥\n";
                playSound("sparkle");
            } 
            else if(streak >= 5 && streak < 10) {
                color.set(ConsoleColor::YELLOW);
                cout << "⚡ MEGA COMBO x" << streak << "! ⚡\n";
                playSound("magic");
                shakeScreen();
            }
            else if(streak >= 10) {
                color.set(ConsoleColor::MAGENTA);
                cout << "🌟🌟🌟 LEGENDARY COMBO x" << streak << "! 🌟🌟🌟\n";
                playSound("thunder");
                shakeScreen();
                shakeScreen();
            }
            color.reset();
        } 
        else if(elapsed > 2000) {
            if(streak > 0) {
                cout << "💔 Combo broken! Streak: " << streak << "\n";
                streak = 0;
                comboMultiplier = 1;
            }
        }
        
        lastKeyTime = now;
    }
    
    //=========================================================================
    // PROCESS REGULAR KEY PRESS
    //=========================================================================
    void processKey(char key) {
        totalKeys++;
        int pointsEarned = 10 * comboMultiplier;
        score += pointsEarned;
        
        // Display key reaction
        color.set(ConsoleColor::YELLOW);
        cout << "\n╔══════════════════════════════════════════╗\n";
        cout << "║  🎯 KEY PRESSED: '" << key << "'";
        
        char lowerKey = tolower(key);
        if(keyReactions.find(lowerKey) != keyReactions.end()) {
            color.set(ConsoleColor::CYAN);
            cout << " → " << keyReactions[lowerKey];
        } else {
            cout << " → 🎮 POWER SHOT!";
        }
        
        cout << "\n╚══════════════════════════════════════════╝\n";
        color.reset();
        
        // Special reactions for different key types
        if(isdigit(key)) {
            color.set(ConsoleColor::BLUE);
            cout << "🔢 DIGIT BONUS! +15 POINTS! 🔢\n";
            score += 15;
            playSound("magic");
            color.reset();
        }
        
        if(isalpha(key)) {
            char vowelCheck = tolower(key);
            if(vowelCheck == 'a' || vowelCheck == 'e' || vowelCheck == 'i' || 
               vowelCheck == 'o' || vowelCheck == 'u') {
                color.set(ConsoleColor::MAGENTA);
                cout << "🎵 VOWEL POWER! +5 EXTRA! 🎵\n";
                score += 5;
                playSound("sparkle");
                color.reset();
            }
        }
        
        // Random bonus events (5% chance)
        if(rand() % 20 == 0) {
            color.set(ConsoleColor::GREEN);
            int bonus = 25 + (rand() % 50);
            cout << "🎁 RANDOM BONUS! +" << bonus << " POINTS! 🎁\n";
            score += bonus;
            playSound("magic");
            color.reset();
        }
        
        // Update combo
        updateCombo();
        
        // Level up check
        if(score >= level * 500) {
            levelUp();
        }
        
        // Display stats
        displayStats();
    }
    
    //=========================================================================
    // LEVEL UP SYSTEM
    //=========================================================================
    void levelUp() {
        level++;
        color.set(ConsoleColor::GOLD);
        cout << "\n╔══════════════════════════════════════════╗\n";
        cout << "║         🏆 LEVEL UP! LEVEL " << level << "! 🏆          ║\n";
        cout << "║     +100 BONUS POINTS!                ║\n";
        cout << "╚══════════════════════════════════════════╝\n";
        color.reset();
        
        score += 100;
        playSound("thunder");
        playAnimation("sparkle");
        shakeScreen();
    }
    
    //=========================================================================
    // CHECK FOR SECRET WORDS
    //=========================================================================
    void checkSecretWord() {
        string checkWord = currentWord;
        transform(checkWord.begin(), checkWord.end(), checkWord.begin(), ::tolower);
        
        for(auto& secret : secretWords) {
            if(checkWord.find(secret.first) != string::npos) {
                secretWordsFound++;
                ReactionEffect effect = secret.second;
                
                color.set(ConsoleColor::RED);
                cout << "\n╔══════════════════════════════════════════╗\n";
                cout << "║   🎉🎉🎉 SECRET WORD FOUND! 🎉🎉🎉     ║\n";
                cout << "║   \"" << secret.first << "\" - " << effect.message << "\n";
                cout << "║   +" << effect.bonusPoints << " POINTS!          ║\n";
                cout << "╚══════════════════════════════════════════╝\n";
                color.reset();
                
                score += effect.bonusPoints;
                playSound(effect.soundType);
                playAnimation(effect.animation);
                shakeScreen();
                
                // Achievement for finding all secrets
                if(secretWordsFound == secretWords.size()) {
                    color.set(ConsoleColor::GOLD);
                    cout << "\n🌟🌟🌟 MASTER DETECTIVE ACHIEVEMENT! +1000 POINTS! 🌟🌟🌟\n";
                    score += 1000;
                    playSound("cosmic");
                    color.reset();
                }
                
                break;
            }
        }
        
        currentWord.clear();
    }
    
    //=========================================================================
    // DISPLAY CURRENT GAME STATISTICS
    //=========================================================================
    void displayStats() {
        auto now = steady_clock::now();
        auto elapsed = duration_cast<seconds>(now - gameStartTime).count();
        int minutes = elapsed / 60;
        int seconds = elapsed % 60;
        
        color.set(ConsoleColor::WHITE);
        cout << "\n┌────────────────────────────────────────────┐\n";
        cout << "│ 📊 STATISTICS                              │\n";
        cout << "├────────────────────────────────────────────┤\n";
        color.set(ConsoleColor::GREEN);
        cout << "│ 🎯 SCORE: " << score << " / " << highScore << " (HIGH)";
        printf(" %*s│\n", 18 - (int)to_string(score).length() - (int)to_string(highScore).length(), "");
        color.set(ConsoleColor::YELLOW);
        cout << "│ ⚡ LEVEL: " << level;
        printf(" %*s│\n", 35, "");
        cout << "│ 🔥 COMBO: x" << streak;
        printf(" %*s│\n", 33, "");
        cout << "│ ⌨️  KEYS: " << totalKeys;
        printf(" %*s│\n", 34, "");
        cout << "│ ⏱️  TIME: " << minutes << "m " << seconds << "s";
        printf(" %*s│\n", 26, "");
        cout << "│ 🎁 SECRETS: " << secretWordsFound << "/" << secretWords.size();
        printf(" %*s│\n", 26, "");
        color.set(ConsoleColor::WHITE);
        cout << "└────────────────────────────────────────────┘\n";
        color.reset();
        
        cout << "\n📝 Current Word: \"" << currentWord << "\"\n";
        cout << "──────────────────────────────────────────────\n";
        cout << "💡 TIP: Type FAST for combos! Find SECRET WORDS for bonuses!\n";
        cout << "──────────────────────────────────────────────\n";
    }
    
    //=========================================================================
    // DISPLAY WELCOME SCREEN
    //=========================================================================
    void showWelcomeScreen() {
        system("cls");
        
        // Big Title
        color.set(ConsoleColor::CYAN);
        cout << R"(
╔═══════════════════════════════════════════════════════════════════════════════╗
║                                                                               ║
║     ████████╗██╗   ██╗██████╗ ███████╗    ██████╗ ███████╗ █████╗  ██████╗    ║
║     ╚══██╔══╝╚██╗ ██╔╝██╔══██╗██╔════╝    ██╔══██╗██╔════╝██╔══██╗██╔════╝    ║
║        ██║    ╚████╔╝ ██████╔╝█████╗      ██████╔╝█████╗  ███████║██║         ║
║        ██║     ╚██╔╝  ██╔═══╝ ██╔══╝      ██╔══██╗██╔══╝  ██╔══██║██║         ║
║        ██║      ██║   ██║     ███████╗    ██║  ██║███████╗██║  ██║╚██████╗    ║
║        ╚═╝      ╚═╝   ╚═╝     ╚══════╝    ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝    ║
║                                                                               ║
║                    ██████╗ ███████╗ █████╗  ██████╗████████╗                  ║
║                    ██╔══██╗██╔════╝██╔══██╗██╔════╝╚══██╔══╝                  ║
║                    ██████╔╝█████╗  ███████║██║        ██║                     ║
║                    ██╔══██╗██╔══╝  ██╔══██║██║        ██║                     ║
║                    ██║  ██║███████╗██║  ██║╚██████╗   ██║                     ║
║                    ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝   ╚═╝                     ║
║                                                                               ║
║                           ⚡ TYPING REACTOR 3000 ⚡                            ║
║                                                                               ║
║                    "Every Keystroke Creates a Digital Storm"                  ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝
)";
        color.reset();
        
        // Game Instructions
        color.set(ConsoleColor::YELLOW);
        cout << "\n\n╔══════════════════════════════════════════════════════════════╗\n";
        cout << "║                      🎮 HOW TO PLAY 🎮                        ║\n";
        cout << "╠══════════════════════════════════════════════════════════════╣\n";
        color.set(ConsoleColor::GREEN);
        cout << "║  • Type ANY letter (A-Z) or number (0-9) to earn points!     ║\n";
        cout << "║  • Type FAST to build COMBO streaks for bonus points!        ║\n";
        cout << "║  • Discover SECRET WORDS for massive bonuses!                ║\n";
        cout << "║  • Press ENTER to check your current word for secrets!       ║\n";
        cout << "║  • Press BACKSPACE to delete (costs 5 points!)               ║\n";
        cout << "║  • Press ESC to exit the game                                ║\n";
        color.set(ConsoleColor::MAGENTA);
        cout << "╠══════════════════════════════════════════════════════════════╣\n";
        cout << "║                     🌟 SECRET WORDS 🌟                        ║\n";
        cout << "║   boom • rainbow • glitch • dragon • magic                   ║\n";
        cout << "║   sparkle • thunder • phoenix • galaxy • nebula              ║\n";
        color.set(ConsoleColor::CYAN);
        cout << "╠══════════════════════════════════════════════════════════════╣\n";
        cout << "║              🏆 HIGH SCORE TO BEAT: " << highScore;
        printf(" %*s║\n", 25 - (int)to_string(highScore).length(), "");
        color.set(ConsoleColor::YELLOW);
        cout << "╚══════════════════════════════════════════════════════════════╝\n";
        color.reset();
        
        cout << "\n\n⚡ PRESS ANY KEY TO START YOUR TYPING ADVENTURE! ⚡\n";
        _getch();
        system("cls");
    }
    
    //=========================================================================
    // DISPLAY GAME OVER SCREEN
    //=========================================================================
    void showGameOverScreen() {
        system("cls");
        
        auto now = steady_clock::now();
        auto elapsed = duration_cast<seconds>(now - gameStartTime).count();
        int minutes = elapsed / 60;
        int seconds = elapsed % 60;
        
        color.set(ConsoleColor::RED);
        cout << R"(
╔══════════════════════════════════════════════════════════════════╗
║                         GAME OVER!                               ║
╚══════════════════════════════════════════════════════════════════╝
)";
        color.reset();
        
        color.set(ConsoleColor::GREEN);
        cout << "\n╔══════════════════════════════════════════════════════════╗\n";
        cout << "║                  🏆 FINAL STATISTICS 🏆                   ║\n";
        cout << "╠══════════════════════════════════════════════════════════╣\n";
        cout << "║  📊 FINAL SCORE: " << score;
        printf(" %*s║\n", 35 - (int)to_string(score).length(), "");
        cout << "║  🏅 HIGH SCORE: " << highScore;
        printf(" %*s║\n", 35 - (int)to_string(highScore).length(), "");
        cout << "║  ⚡ LEVEL REACHED: " << level;
        printf(" %*s║\n", 33, "");
        cout << "║  ⌨️  TOTAL KEYS: " << totalKeys;
        printf(" %*s║\n", 34, "");
        cout << "║  🔥 MAX COMBO: " << streak;
        printf(" %*s║\n", 35, "");
        cout << "║  🎁 SECRETS FOUND: " << secretWordsFound << "/" << secretWords.size();
        printf(" %*s║\n", 26, "");
        cout << "║  ⏱️  TIME PLAYED: " << minutes << "m " << seconds << "s";
        printf(" %*s║\n", 26, "");
        color.set(ConsoleColor::YELLOW);
        
        // Rating based on performance
        if(score > 5000) {
            cout << "║  🌟🌟🌟🌟🌟 LEGENDARY TYPIST MASTER! 🌟🌟🌟🌟🌟  ║\n";
        } else if(score > 3000) {
            cout << "║  🌟🌟🌟🌟 INCREDIBLE PERFORMANCE! 🌟🌟🌟🌟      ║\n";
        } else if(score > 1500) {
            cout << "║  🌟🌟🌟 GREAT JOB, TYPING WARRIOR! 🌟🌟🌟        ║\n";
        } else if(score > 500) {
            cout << "║  🌟🌟 GOOD START! PLAY AGAIN TO IMPROVE! 🌟🌟      ║\n";
        } else {
            cout << "║  🌟 KEEP PRACTICING! SPEED UP FOR BIG POINTS! 🌟   ║\n";
        }
        
        color.set(ConsoleColor::CYAN);
        cout << "╚══════════════════════════════════════════════════════════╝\n";
        color.reset();
        
        if(score > highScore) {
            color.set(ConsoleColor::GOLD);
            cout << "\n🎉🎉🎉 NEW HIGH SCORE! CONGRATULATIONS! 🎉🎉🎉\n";
            color.reset();
        }
        
        cout << "\n\nPress any key to exit...";
        _getch();
    }
    
    //=========================================================================
    // MAIN GAME LOOP
    //=========================================================================
    void run() {
        showWelcomeScreen();
        
        char key;
        bool running = true;
        
        while(running) {
            if(_kbhit()) {
                key = _getch();
                
                switch(key) {
                    case 27: // ESC key
                        running = false;
                        break;
                        
                    case 13: // Enter key
                        if(!currentWord.empty()) {
                            checkSecretWord();
                        } else {
                            color.set(ConsoleColor::YELLOW);
                            cout << "\n💡 Type something first to check for secret words!\n";
                            color.reset();
                        }
                        displayStats();
                        break;
                        
                    case 8: // Backspace
                        if(!currentWord.empty()) {
                            currentWord.pop_back();
                            score = max(0, score - 5);
                            color.set(ConsoleColor::RED);
                            cout << "\n🔙 BACKSPACE! -5 points\n";
                            color.reset();
                            displayStats();
                        }
                        break;
                        
                    case 32: // Space
                        currentWord += ' ';
                        processKey(' ');
                        break;
                        
                    default:
                        if(isalnum(key)) {
                            currentWord += key;
                            processKey(key);
                        }
                        break;
                }
            }
            this_thread::sleep_for(milliseconds(10));
        }
        
        saveHighScore();
        showGameOverScreen();
    }
};

//=============================================================================
// MAIN FUNCTION - ENTRY POINT
//=============================================================================
int main() {
    // Set console window title and size
    SetConsoleTitle(TEXT("⚡ TYPE REACTOR 3000 - Ultimate Typing Reaction Game ⚡"));
    system("mode con cols=100 lines=45");
    
    // Disable cursor blinking for cleaner display
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
    // Create and run the game
    TypeReactor3000 game;
    game.run();
    
    return 0;
}
