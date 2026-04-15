#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>
#include <conio.h>     // Windows _kbhit(), _getch()
#include <windows.h>   // Windows Beep(), SetConsoleTextAttribute()

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

using namespace std;
using namespace chrono;

// ========== EMBEDDED LOGIC: Reaction Engine ==========
class TypeReactor {
private:
    int score;
    int streak;
    int totalKeys;
    map<char, string> reactions;
    vector<string> secretWords;
    steady_clock::time_point lastKeyTime;
    
    // Color codes for Windows console
    enum Color {
        RESET = 7,
        RED = 12,
        GREEN = 10,
        YELLOW = 14,
        BLUE = 9,
        MAGENTA = 13,
        CYAN = 11,
        WHITE = 15
    };
    
public:
    TypeReactor() : score(0), streak(0), totalKeys(0) {
        srand(time(0));
        initReactions();
        initSecretWords();
        lastKeyTime = steady_clock::now();
    }
    
    void initReactions() {
        reactions = {
            {'a', "✨ SPARKLE! ✨"},
            {'b', "🦋 BUTTERFLY!"},
            {'c', "🐱 CAT SOUND: Meow!"},
            {'d', "💃 DANCE BREAK!"},
            {'e', "⚡ ELECTRIC SHOCK!"},
            {'f', "🔥 FIREBALL!"},
            {'g', "🎮 GAME BONUS!"},
            {'h', "❤️ HEART ATTACK!"},
            {'i', "🍦 ICE CREAM!"},
            {'j', "🤡 JOKER LAUGH!"},
            {'k', "🔑 KEY FOUND!"},
            {'l', "🌈 LASER LIGHT!"},
            {'m', "🌙 MOON JUMP!"},
            {'n', "🎵 NOTE PLAYED!"},
            {'o', "🌀 ORBIT SPIN!"},
            {'p', "🎉 PARTY POP!"},
            {'q', "❓ QUESTION MAGIC!"},
            {'r', "🤖 ROBOT DANCE!"},
            {'s', "⭐ SUPERNOVA!"},
            {'t', "🚀 TAKEOFF!"},
            {'u', "☂️ UMBRELLA FLOAT!"},
            {'v', "🎻 VIOLIN SOLO!"},
            {'w', "🌊 WAVE SURF!"},
            {'x', "❌ X-RAY VISION!"},
            {'y', "💛 YELLOW YOYO!"},
            {'z', "⚡ ZAP ZAP ZAP!"},
            {' ', "🕊️ SPACE WARP!"},
            {'0', "🔴 RED ALERT!"},
            {'1', "🟡 ONE HIT COMBO!"},
            {'2', "🔵 DOUBLE TROUBLE!"},
            {'3', "🟣 TRIPLE THREAT!"},
            {'4', "🟢 FOUR WINDS!"},
            {'5', "🟠 FIVE STAR!"},
            {'6', "📀 SIX PACK!"},
            {'7', "🌈 SEVEN COLORS!"},
            {'8', "🐙 OCTOPUS ATTACK!"},
            {'9', "🌙 NINE LIVES!"}
        };
    }
    
    void initSecretWords() {
        secretWords = {"boom", "rainbow", "glitch", "dragon", "magic", 
                       "sparkle", "thunder", "phoenix", "galaxy", "nebula"};
    }
    
    void setColor(int color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
    
    void playBeep(int frequency, int duration) {
        Beep(frequency, duration);
    }
    
    void shakeScreen() {
        // Simple screen shake effect by printing newlines
        cout << "\n";
        for(int i = 0; i < 3; i++) {
            cout << "⚡⚡⚡ SHAKE! ⚡⚡⚡\r";
            this_thread::sleep_for(milliseconds(50));
            cout << "   SHAKE!      \r";
            this_thread::sleep_for(milliseconds(50));
        }
        cout << "                \r";
    }
    
    void showTypingEffect(char c) {
        // Visual feedback with colors
        setColor(YELLOW);
        cout << "\n┌─────────────────────────────────┐\n";
        cout << "│  YOU TYPED: '" << c << "'";
        
        if(reactions.find(tolower(c)) != reactions.end()) {
            setColor(GREEN);
            cout << " → " << reactions[tolower(c)];
        } else {
            setColor(CYAN);
            cout << " → 🎯 GOOD SHOT!";
        }
        
        cout << "\n└─────────────────────────────────┘\n";
        setColor(RESET);
    }
    
    void checkStreak() {
        auto now = steady_clock::now();
        auto elapsed = duration_cast<milliseconds>(now - lastKeyTime).count();
        
        if(elapsed < 500) { // Fast typing (within 0.5 seconds)
            streak++;
            setColor(MAGENTA);
            cout << "🔥 COMBO x" << streak << "! 🔥\n";
            playBeep(1000 + (streak * 100), 100);
            setColor(RESET);
            
            if(streak >= 5) {
                setColor(RED);
                cout << "⭐⭐⭐ MEGA STREAK! ⭐⭐⭐\n";
                playBeep(1500, 300);
                shakeScreen();
                score += 50;
                setColor(RESET);
            }
        } else {
            if(streak > 0) {
                cout << "💔 Streak ended at " << streak << "!\n";
            }
            streak = 0;
        }
        
        lastKeyTime = now;
    }
    
    void checkSecretWord(const string& input) {
        string lowerInput = input;
        transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
        
        for(const string& secret : secretWords) {
            if(lowerInput.find(secret) != string::npos) {
                setColor(RED);
                cout << "\n🎉🎉🎉 SECRET WORD DETECTED: " << secret << "! 🎉🎉🎉\n";
                cout << "💎 BONUS +100 POINTS! 💎\n";
                setColor(YELLOW);
                cout << "🌟 SPECIAL EFFECT: ";
                
                if(secret == "boom") {
                    cout << "💥 EXPLOSION! 💥\n";
                    playBeep(200, 500);
                    for(int i = 0; i < 5; i++) {
                        cout << "💥 ";
                        this_thread::sleep_for(milliseconds(100));
                    }
                    cout << "\n";
                } 
                else if(secret == "rainbow") {
                    cout << "🌈 COLOR WAVE! 🌈\n";
                    for(int i = 0; i < 7; i++) {
                        setColor(i + 9);
                        cout << "█";
                        this_thread::sleep_for(milliseconds(50));
                    }
                    setColor(RESET);
                    cout << "\n";
                }
                else if(secret == "glitch") {
                    cout << "🌀 GLITCH MODE ACTIVATED! 🌀\n";
                    shakeScreen();
                    shakeScreen();
                }
                else if(secret == "dragon") {
                    cout << "🐉 DRAGON FIRE BREATH! 🐉\n";
                    playBeep(300, 200);
                    playBeep(400, 200);
                    playBeep(500, 300);
                }
                
                score += 100;
                setColor(RESET);
                break;
            }
        }
    }
    
    void processKey(char c) {
        totalKeys++;
        score += 10;
        
        showTypingEffect(c);
        checkStreak();
        
        // Random bonus events (embedded logic)
        if(rand() % 20 == 0) { // 5% chance
            setColor(BLUE);
            cout << "🎁 RANDOM BONUS! +50 POINTS! 🎁\n";
            score += 50;
            playBeep(1200, 150);
            setColor(RESET);
        }
        
        // Number special reactions
        if(isdigit(c)) {
            setColor(CYAN);
            cout << "🔢 NUMBER POWER! +20 BONUS! 🔢\n";
            score += 20;
            playBeep(880, 100);
            setColor(RESET);
        }
        
        // Vowel power
        char lower = tolower(c);
        if(lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {
            setColor(MAGENTA);
            cout << "🎵 VOWEL VIBE! 🎵\n";
            playBeep(440, 200);
            setColor(RESET);
        }
        
        cout << "\n📊 SCORE: " << score << "  |  STREAK: " << streak << "  |  TOTAL KEYS: " << totalKeys << "\n";
        cout << "────────────────────────────────────────────\n";
    }
    
    void showWelcome() {
        system("cls");
        setColor(CYAN);
        cout << "╔══════════════════════════════════════════╗\n";
        cout << "║        🎮 TYPE REACTOR 3000 🎮           ║\n";
        cout << "║     Every key creates a reaction!        ║\n";
        cout << "╚══════════════════════════════════════════╝\n\n";
        setColor(YELLOW);
        cout << "✨ SECRET WORDS TO DISCOVER:\n";
        cout << "   boom, rainbow, glitch, dragon, magic\n";
        cout << "   sparkle, thunder, phoenix, galaxy, nebula\n\n";
        setColor(GREEN);
        cout << "🎯 HOW TO PLAY:\n";
        cout << "   • Type ANY key to start\n";
        cout << "   • Type FAST for combos\n";
        cout << "   • Find secret words for BIG bonuses\n";
        cout << "   • Press ESC to exit\n\n";
        setColor(RESET);
        cout << "════════════════════════════════════════════\n";
        cout << "👉 START TYPING NOW! 👈\n\n";
    }
    
    void run() {
        showWelcome();
        
        string inputBuffer = "";
        char c;
        
        while(true) {
            if(_kbhit()) {
                c = _getch();
                
                if(c == 27) { // ESC key
                    break;
                }
                else if(c == 13) { // Enter key
                    checkSecretWord(inputBuffer);
                    inputBuffer = "";
                    cout << "\n✨ LINE COMPLETE! +50 BONUS! ✨\n";
                    score += 50;
                    playBeep(800, 200);
                    inputBuffer = "";
                }
                else if(c == 8) { // Backspace
                    if(!inputBuffer.empty()) {
                        inputBuffer.pop_back();
                        cout << "\b \b";
                    }
                    cout << "\n🔙 BACKSPACE! -10 points\n";
                    score = max(0, score - 10);
                }
                else {
                    inputBuffer += c;
                    processKey(c);
                    
                    // Show current word being typed
                    setColor(WHITE);
                    cout << "📝 Current word: " << inputBuffer << "\n";
                    setColor(RESET);
                }
            }
            this_thread::sleep_for(milliseconds(10));
        }
        
        showGameOver();
    }
    
    void showGameOver() {
        system("cls");
        setColor(YELLOW);
        cout << "\n╔══════════════════════════════════════════╗\n";
        cout << "║            GAME OVER! 🎮                 ║\n";
        cout << "╚══════════════════════════════════════════╝\n\n";
        setColor(GREEN);
        cout << "🏆 FINAL STATISTICS:\n";
        cout << "   • Total Score: " << score << "\n";
        cout << "   • Keys Pressed: " << totalKeys << "\n";
        cout << "   • Highest Streak: " << streak << "\n\n";
        
        if(score > 500) {
            setColor(MAGENTA);
            cout << "🌟🌟🌟 LEGENDARY TYPIST! 🌟🌟🌟\n";
        } else if(score > 200) {
            setColor(CYAN);
            cout << "⭐ AWESOME PERFORMANCE! ⭐\n";
        } else {
            setColor(YELLOW);
            cout << "👍 GOOD JOB! PLAY AGAIN TO BEAT YOUR SCORE! 👍\n";
        }
        
        setColor(RESET);
        cout << "\nPress any key to exit...";
        _getch();
    }
};

// ========== MAIN FUNCTION ==========
int main() {
    // Set console title
    SetConsoleTitle(TEXT("🎮 TYPE REACTOR 3000 - Typing Arcade Game"));
    
    // Maximize console window for better experience
    system("mode con cols=80 lines=30");
    
    TypeReactor game;
    game.run();
    
    return 0;
}
