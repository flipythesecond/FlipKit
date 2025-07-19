//┌--------------------------------------------------------------------------------------------------------┐
//| Flipkit/source/fliplist.cpp                                                                            |
//| Author: Bek A.                                                                                         |
//| Last Updated: 7/19/2025                                                                                |
//| License: GNU General Public License v3.0                                                               |
//| Description: This source file implements the Fliplist password generator tool.                         |
//|              It provides interactive and dictionary-based password generation for penetration testing. |
//|              This file should be compiled as part of the Flipkit toolkit.                              |
//└--------------------------------------------------------------------------------------------------------┘
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include "osdetect.h"
#include "asciiart.h"
#include "cursor.h"

using namespace std;

// Function Prototypes
void runFliplist();
void printFliplistAsciiArt();
int safeStoi(const string& s);
string getCharsetInteractive();
size_t calculateTotal(const string& charset, int minLen, int maxLen);
void generatePasswords(const string& charset, const string& keyphrase, int minLen, int maxLen, size_t& count, size_t total, int mode, ofstream& outfile, string current = "");


//Main function to run Fliplist
int main() {
    hideCursor(); // Hide the console cursor for better user experience
    printFliplistAsciiArt();
    showCursor(); // Show the console cursor after the ASCII art
    runFliplist();
    return 0;
}

//┌------------------------------------------------------------------------------┐
//| This function contains the main logic for Fliplist                           |
//| It provides an interactive menu for users to select password generation modes|
//| and handles the generation process based on user input.                      |
//| HOW TO USE: Call runFliplist() function to run the Fliplist tool             |
//└------------------------------------------------------------------------------┘
void runFliplist() {
    while (true) {
        clearScreen(); // Clear the console screen
        // Display the main menu
        cout << "\n      \033[38;2;0;255;0m[!] Welcome to Fliplist ~(:)<<<<<<>>>>>>>>~\033[0m\n";
        cout << "      \033[38;2;0;255;255m---------------------------------------------\033[0m\n";
        cout << "      \033[38;2;255;255;0mAvailable Modes:\033[0m\n";
        cout << "      \033[38;2;255;255;255m   [1] Custom      - Keyphrase + charset options\033[0m\n";
        cout << "      \033[38;2;255;255;255m   [2] Dictionary  - Charset brute force\033[0m\n";
        cout << "      \033[38;2;0;255;255m---------------------------------------------\033[0m\n";
        cout << "      \033[38;2;255;255;0mSelect mode (1/2, B to back out, Q to quit):\033[0m \n";
        cout << "      \033[38;2;255;255;0m==:>~ \033[0m"; // Prompt for input
        string input; // Input string for mode selection
        string keyphrase; // Keyphrase for custom mode
        bool validateLen = true; // Flag to validate length input

        getline(cin, input); // Read user input

        if (input == "Q" || input == "q") exit(0);
        if (input == "B" || input == "b") return;
        int mode = safeStoi(input);
        if (mode != 1 && mode != 2) {

            // If the mode is invalid, display an error message and continue the loop
            cout << "\n      \033[38;2;255;0;0mInvalid argument.\033[0m\n";
            if(IS_WINDOWS) {
                Sleep(1000); // Pause for 1 second (Windows)
            } else {
                sleep(1); // Pause for 1 second on non-Windows systems
            }
            clearScreen();
            continue;
        }

        clearScreen();

        // Get character set and password length range interactively
        int minLen = 0, maxLen = 0;
        size_t count = 0;
        string charset = getCharsetInteractive();
        if (charset == "BACK") continue;
        if (charset.empty()) {
            cout << "No charset selected. Please choose at least one character set option.\n";
            cout << "Press any key to return to the main menu...\n";
            cin.ignore(1000, '\n'); // Clear input buffer
            cin.get();
            clearScreen(); // Clear the screen before showing the main menu again
            continue;
        }

        // Validate length input
        clearScreen();
        while (validateLen) {
            cout << "\n      \033[38;2;0;255;255m[ Character Set Selected: " << charset << " ]\033[0m\n";
            cout << "      \033[38;2;255;255;0m---------------------------------------------\033[0m\n";
            cout << "      \033[38;2;255;255;0mEnter password length range:\033[0m\n";
            cout << "      \033[38;2;255;255;255m   [!] Minimum length: \033[0m";
            cin >> minLen;
            if (minLen < 1) {
                cout << "\n      \033[38;2;255;0;0mMinimum length must be at least 1.\033[0m\n";
                cin.ignore(1000, '\n'); // Clear input buffer
                if(IS_WINDOWS) {
                    Sleep(1000); // Pause for 1 second (Windows)
                } else {
                    sleep(1); // Pause for 1 second on non-Windows systems
                }
                clearScreen();
                continue;
            }

            cin.ignore(1000, '\n');
            cout << "      \033[38;2;255;255;255m   [!] Maximum length: \033[0m";
            cin >> maxLen;
            

            // Validate length range
            if (maxLen < minLen) {
                cout << "\n      \033[38;2;255;0;0mMaximum length cannot be lower than minimum length.\033[0m\n";
                cin.ignore(); // Clear input buffer
                if(IS_WINDOWS) {
                    Sleep(1000); // Pause for 1 second (Windows)
                } else {
                    sleep(1); // Pause for 1 second on non-Windows systems
                }
                clearScreen();
                continue;
            }

            // Warn if lengths are too large
            if (minLen > 20 || maxLen > 20) {
                cout << "Warning: Lengths greater than 20 may take a long time to generate...\n";
                // Pause for 4 seconds to let the user read the warning
                if (IS_WINDOWS) {
                    Sleep(4000); // Pause for 4 seconds
                } else {
                    sleep(4); // Pause for 4 seconds on non-Windows systems
                }
            }
            validateLen = false; // Reset flag after first validation
        }

        // Calculate total combinations
        size_t total = calculateTotal(charset, minLen, maxLen);

        // Display total combinations
        clearScreen();
        cout << "\n      \033[38;2;255;255;0mTotal combinations: " << total << "\033[0m\n";
        cout << "      \033[38;2;255;255;0m---------------------------------------------\033[0m\n";
        cout << "      \033[38;2;255;255;0mEnter output filename (leave blank for default 'fliplist.txt'): \033[0m";
        string filename;
        getline(cin, filename);
        if (filename.empty()) filename = "fliplist.txt";
        else if (filename.find(".txt") == string::npos) filename += ".txt";

        ofstream outfile(filename);
        if (!outfile) {
            cout << "Error opening file for writing: " << filename << endl;
            continue;
        }

        if (mode == 1) {
            cout << "      Enter keyphrase (leave blank for none): ";
            getline(cin, keyphrase);
            int pos = 0;
            if (!keyphrase.empty()) {
                cout << "\n      \033[38;2;255;255;0mWhere to append charset?\033[0m\n";
                cout << "\033[38;2;255;255;255m   [1] Beginning\n   [2] Middle\n   [3] End\033[0m\n";
                cout << "      Enter choice (1/2/3, B to go back): ";
                getline(cin, input);
                if (input == "B" || input == "b") continue;
                pos = safeStoi(input);
                if (pos < 1 || pos > 3) continue;
            }
            generatePasswords(charset, keyphrase, minLen, maxLen, count, total, pos, outfile);
        } else {
            // Dictionary mode: just brute-force all combinations
            generatePasswords(charset, "", minLen, maxLen, count, total, 0, outfile);
        }
        
        clearScreen();
        outfile.close();
        cout << "\n      \033[38;2;0;255;0m[!] Password generation complete!\033[0m\n";
        cout << "      \033[38;2;255;255;0mTotal passwords generated: " << count << "\033[0m\n";
        cout << "      \033[38;2;255;255;0mOutput written to: " << filename << "\033[0m\n";
        if(!keyphrase.empty()) {
            cout << "      \033[38;2;255;255;0mKeyphrase used: " << keyphrase << "\033[0m\n";
        }
        cout << "      \033[38;2;255;255;0mPress any key to return to the main menu...\033[0m\n";
        cin.get(); // Wait for user input before returning to the main menu
        clearScreen(); // Clear the screen before showing the main menu again
    }
}



// Get charset interactively

string getCharsetInteractive() {
    bool upper = false, lower = false, num = false, sym = false;
    char choice;
    while (true) {
        clearScreen();
        cout << "\n      \033[38;2;0;255;255m[ Character Set Selection ]\033[0m\n";
        cout << "      \033[38;2;255;255;255mToggle options (U/L/N/S)\033[0m\n\n";
        cout << "      " << (upper ? "\033[38;2;0;255;0m[U] Uppercase (A-Z)\033[0m" : "\033[38;2;255;0;0m[U] Uppercase (A-Z)\033[0m") << endl;
        cout << "      " << (lower ? "\033[38;2;0;255;0m[L] Lowercase (a-z)\033[0m" : "\033[38;2;255;0;0m[L] Lowercase (a-z)\033[0m") << endl;
        cout << "      " << (num   ? "\033[38;2;0;255;0m[N] Numbers (0-9)\033[0m"   : "\033[38;2;255;0;0m[N] Numbers (0-9)\033[0m") << endl;
        cout << "      " << (sym   ? "\033[38;2;0;255;0m[S] Symbols (!@#...)\033[0m": "\033[38;2;255;0;0m[S] Symbols (!@#...)\033[0m") << endl;
        cout << "\n      \033[38;2;255;255;0mYour selection will be highlighted in green.\033[0m\n";
        cout << "      \033[38;2;255;255;255mPress key to toggle, ENTER to confirm, B to go back.\033[0m\n";
        cout << "      \033[38;2;255;255;0m==:>~ \033[0m";
        choice = cin.get();
        choice = toupper(choice);
        if (choice == '\n') break;
        if (choice == 'U') upper = !upper;
        if (choice == 'L') lower = !lower;
        if (choice == 'N') num   = !num;
        if (choice == 'S') sym   = !sym;
        if (choice == 'B') return "BACK";
        cin.ignore(1000, '\n'); // Clear input buffer
    }
    string charset;
    if (upper) charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (lower) charset += "abcdefghijklmnopqrstuvwxyz";
    if (num)   charset += "0123456789";
    if (sym)   charset += "!@#$%^&*()-_=+[]{}|;:',.<>/?";
    return charset;
}

size_t calculateTotal(const string& charset, int minLen, int maxLen) {
    size_t total = 0;
    for (int len = minLen; len <= maxLen; ++len) {
        size_t combos = 1;
        for (int i = 0; i < len; ++i) combos *= charset.size();
        total += combos;
    }
    return total;
}



int safeStoi(const string& s) {
    try {
        return stoi(s);
    } catch (...) {
        return -1;
    }
}



void generatePasswords(
    const string& charset,
    const string& keyphrase,
    int minLen,
    int maxLen,
    size_t& count,
    size_t total,
    int mode, // 0: dictionary, 1: prepend, 2: middle, 3: append
    ofstream& outfile,
    string current
) {
    if (current.length() >= minLen && current.length() <= maxLen) {
        string password;
        if (mode == 0) {
            password = current;
        } else if (mode == 1) {
            password = keyphrase + current;
        } else if (mode == 2) {
            size_t mid = keyphrase.length() / 2;
            password = keyphrase.substr(0, mid) + current + keyphrase.substr(mid);
        } else if (mode == 3) {
            password = current + keyphrase;
        }
        outfile << password << endl; // Write to file
        ++count;
        if (count % 1000 == 0 || count == total) {
            clearScreen();
            int barWidth = 40;
            float progress = float(count) / total;
            cout << "\033[38;2;0;255;255mProgress: " << count << " / " << total << "\033[0m\n";
            cout << "\r\033[38;2;0;255;255m[";
            int pos = barWidth * progress;
            for (int j = 0; j < barWidth; ++j) {
                if (j < pos) cout << ">";
                else if (j == pos) cout << "<:>~";
                else cout << " ";
            }
            cout << "] " << int(progress * 100.0) << "%\033[0m";
            cout.flush();
        }
    }
    if (current.length() == maxLen) return;
    for (char c : charset) {
        generatePasswords(charset, keyphrase, minLen, maxLen, count, total, mode, outfile, current + c);
    }
}