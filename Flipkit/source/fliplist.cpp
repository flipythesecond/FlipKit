//┌--------------------------------------------------------------------------------------------------------┐
//| Flipkit/source/fliplist.cpp                                                                            |
//| Author: B.A.                                                                                           |
//| Last Updated: 7/19/2025                                                                                |
//| License: GNU General Public License v3.0                                                               |
//| Description: This source file implements the Fliplist password generator tool.                         |
//|              It provides interactive and dictionary-based password generation for penetration testing. |
//|              This file should be compiled as part of the Flipkit toolkit.                              |
//└--------------------------------------------------------------------------------------------------------┘
#include <iostream> // For standard input/output operations
#include <vector> // For vector operations
#include <string> // For string operations
#include <algorithm> // For std::sort
#include <cstdlib> // For system calls
#include <windows.h> // For Sleep function on Windows
#include <fstream> // For file operations
#include <limits> // For std::numeric_limits
#include <iomanip> // For std::setprecision
#include "osdetect.h" // For OS detection macros
#include "asciiart.h" // For ASCII art functions
#include "cursor.h" // For cursor visibility functions
#include <csignal> // For signal handling

using namespace std;

// Function Prototypes
void runFliplist();
void printFliplistAsciiArt();
int safeStoi(const string& s);
string getCharsetInteractive();
void resetConsoleColor(int);
size_t calculateTotal(const string& charset, int minLen, int maxLen, int keyphraseLen = 0);
void generatePasswords(const string& charset, const string& keyphrase, int minLen, int maxLen, size_t& count, size_t total, int mode, ofstream& outfile, string current = "");


//Main function to run Fliplist
int main() {
    signal(SIGINT, resetConsoleColor); // Handle Ctrl+C
    hideCursor(); // Hide cursor during animation
    printFliplistAsciiArt();
    cout.flush(); // Flush ASCII art output
    showCursor(); // Show cursor after the animation
    runFliplist(); // Run the Fliplist tool
    std::cout << "\033[0m"; // Reset color before exit
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
        clearScreen();
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

        string filename; // Output filename for generated passwords
        
        bool validateLen = true; // Flag to validate length input

        getline(cin, input); // Read user input

        if (input == "Q" || input == "q"){ 
            std::cout << "\033[0m"; // Reset color before exit
            exit(0);
        }
        if (input == "B" || input == "b") {
            std::cout << "\033[0m"; // Reset color before returning
            return;
        }
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
        string keyphrase;
        int pos = 0;

        // Get character set first
        string charset = getCharsetInteractive();
        if (charset == "BACK") continue;
        if (charset.empty()) {
            cout << "No charset selected. Please choose at least one character set option.\n";
            cout << "Press any key to return to the main menu...\n";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            clearScreen();
            continue;
        }

        // Prompt for keyphrase and position if in custom mode
        if (mode == 1) {
            cout << "      Enter keyphrase (leave blank for none): ";
            getline(cin, keyphrase);
            if (!keyphrase.empty()) {
                cout << "\n      \033[38;2;255;255;0mWhere to append keyphrase?\033[0m\n";
                cout << "\033[38;2;255;255;255m   [1] Beginning\n   [2] Middle\n   [3] End\033[0m\n";
                cout << "      Enter choice (1/2/3, B to go back): ";
                string input;
                getline(cin, input);
                if (input == "B" || input == "b") continue;
                pos = safeStoi(input);
                if (pos < 1 || pos > 3) {
                    cout << "\n      \033[38;2;255;0;0mInvalid position. Please enter 1, 2, or 3.\033[0m\n";
                    if(IS_WINDOWS) Sleep(1000); else sleep(1);
                    clearScreen();
                    continue;
                }
            }
        }

        // Validate length input
        validateLen = true;
        while (validateLen) {
            clearScreen();
            cout << "\n      \033[38;2;0;255;255m[ Character Set Selected: " << charset << " ]\033[0m\n";
            // Show keyphrase again above length selection menu if present
            cout << endl;
            if (mode == 1 && !keyphrase.empty()) {
                cout << "      \033[38;2;255;255;0mKeyphrase: \033[38;2;0;255;255m" << keyphrase << "\033[0m\n";
            }
            cout << "      \033[38;2;255;255;0m[!] Password Length Selection\033[0m\n";
            cout << "      \033[38;2;255;255;0m---------------------------------------------\033[0m\n";
            cout << "      \033[38;2;255;255;0mEnter password length range:\033[0m\n";
            cout << "      \033[38;2;255;255;255m   [!] Minimum length: \033[0m";
            cin >> minLen;
            if (minLen < 1) {
                cout << "\n      \033[38;2;255;0;0mMinimum length must be at least 1.\033[0m\n";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if(IS_WINDOWS) Sleep(1000); else sleep(1);
                clearScreen();
                continue;
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "      \033[38;2;255;255;255m   [!] Maximum length: \033[0m";
            cin >> maxLen;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (maxLen < minLen) {
                cout << "\n      \033[38;2;255;0;0mMaximum length cannot be lower than minimum length.\033[0m\n";
                if(IS_WINDOWS) Sleep(1000); else sleep(1);
                clearScreen();
                continue;
            }

            // If keyphrase is set, minLen and maxLen must be >= keyphrase.length()
            if (mode == 1 && !keyphrase.empty() && (minLen < keyphrase.length() || maxLen < keyphrase.length())) {
                cout << "\n      \033[38;2;255;0;0mMinimum and maximum length must be at least as long as the keyphrase (\033[38;2;0;128;255m" << keyphrase << "\033[38;2;255;0;0m).\033[0m\n";
                if(IS_WINDOWS){ Sleep(2500); } else{ sleep(1); }
                clearScreen();
                continue;
            }

            if (minLen > 20 || maxLen > 20) {
                cout << "Warning: Lengths greater than 20 may take a long time to generate...\n";
                if (IS_WINDOWS) Sleep(4000); else sleep(4);
            }
            validateLen = false;
        }

        // Calculate total combinations
        size_t total;
        if (mode == 1) {
            // Custom mode: include keyphrase length
            total = calculateTotal(charset, minLen, maxLen, keyphrase.length());
        } else {
            // Dictionary mode: no keyphrase
            total = calculateTotal(charset, minLen, maxLen);
        }

        // Display total combinations
        clearScreen();
     
        ofstream outfile; // Declare outfile here so it's visible after both blocks

        // Prompt for output filename and keyphrase if in custom mode
        if (mode == 1) {

            cout << "      \033[38;2;0;255;255m----------------------------------------------------------\033[0m\n";
            cout << "\n    \033[38;2;0;255;255m[ Custom Mode Selected ]\033[0m\n";
            cout << "      \033[38;2;255;255;0mCharset: " <<  "\033[38;2;0;255;255m" << charset << "\033[0m\n";
            cout << "      \033[38;2;255;255;0mKeyphrase: " << (keyphrase.empty() ? "\033[38;2;255;0;0mNone" : "\033[38;2;0;255;255m" + keyphrase) << "\033[0m\n";
            cout << "      \033[38;2;255;255;0mLength Range: " << "\033[38;2;0;255;255m" << minLen << " to " << "\033[38;2;0;255;255m" << maxLen << "\033[0m\n";
            cout << "      \033[38;2;255;255;0mTotal combinations: " << "\033[38;2;0;255;255m" << total << "\033[0m\n";
            cout << "      \033[38;2;255;255;0m----------------------------------------------------------\033[0m\n";
            cout << "      \033[38;2;255;255;0mEnter output filename (leave blank for default 'fliplist.txt'): \033[0m";
            getline(cin, filename);
            
            if (filename.empty()) filename = "fliplist.txt";
            else if (filename.find(".txt") == string::npos) filename += ".txt";


            // Check if file already exists
            ifstream checkFile(filename);
            if (checkFile) {
                cout << "       \033[38;2;255;255;0mFile already exists. Overwrite? (Y/n): \033[0m";
                string choice;
                getline(cin, choice);

                if (choice.empty()) {
                    choice = "Y"; // Default to 'Y' if no input
                }
                
                //If user chooses not to overwrite, take them back to the main menu
                else if (choice != "Y" && choice != "y") {
                    continue;
                }
            }
            checkFile.close(); // Close the file after checking

            outfile.open(filename);
            if (!outfile) {
                cout << "Error opening file for writing: " << filename << endl;
                continue;
            }
            clearScreen();
            // Display custom mode details
            hideCursor(); // Hide cursor during generation
            cout << endl; // New line for better readability
            cout << "      \033[38;2;0;255;255m----------------------------------------------------------\033[0m\n";
            cout << "\n      \033[38;2;0;255;255m[ Custom Mode Selected ]\033[0m\n";
            cout << "      \033[38;2;255;255;0mCharset: " <<  "\033[38;2;0;255;255m" << charset << "\033[0m\n";
            cout << "      \033[38;2;255;255;0mKeyphrase: " << (keyphrase.empty() ? "\033[38;2;255;0;0mNone" : "\033[38;2;0;255;255m" + keyphrase) << "\033[0m\n";
            cout << "      \033[38;2;255;255;0mLength Range: " << "\033[38;2;0;255;255m" << minLen << " to " << "\033[38;2;0;255;255m" << maxLen << "\033[0m\n";
            cout << "      \033[38;2;255;255;0mTotal combinations: " << "\033[38;2;0;255;255m" << total << "\033[0m\n";
            cout << "      \033[38;2;255;255;0m----------------------------------------------------------\033[0m\n";
            // Custom mode: generate passwords with keyphrase
            generatePasswords(charset, keyphrase, minLen, maxLen, count, total, pos, outfile);
        } 
        // If mode is 2 (dictionary), prompt for output filename
        else{
            cout << "      \033[38;2;255;255;0mEnter output filename (leave blank for default 'fliplist.txt'): \033[0m";
            
            
            // Prompt for output filename
            getline(cin, filename);
            if (filename.empty()) filename = "fliplist.txt";
            else if (filename.find(".txt") == string::npos) filename += ".txt";

            ifstream checkFile(filename);
            if (checkFile) {
                cout << "       \033[38;2;255;255;0mFile already exists. Overwrite? (Y/n): \033[0m";
                string choice;
                getline(cin, choice);

                if (choice.empty()) {
                    choice = "Y"; // Default to 'Y' if no input
                }
                
                //If user chooses not to overwrite, take them back to the main menu
                else if (choice != "Y" && choice != "y") {
                    continue;
                }
            }
            checkFile.close(); // Close the file after checking
            outfile.open(filename);
            if (!outfile) {
                cout << "Error opening file for writing: " << filename << endl;
                continue;
            }
            clearScreen();
            // Display dictionary mode details
            hideCursor(); // Hide cursor during generation
            cout << endl; // New line for better readability
            cout << "      \033[38;2;255;255;0m----------------------------------------------------------\033[0m\n";
            cout << "\n      \033[38;2;0;255;0m[ Custom Mode Selected ]\033[0m\n";
            cout << "      \033[38;2;255;255;0mCharset: " <<  "\033[38;2;0;255;255m" << charset << "\033[0m\n";
            cout << "      \033[38;2;255;255;0mKeyphrase: " << (keyphrase.empty() ? "\033[38;2;255;0;0mNone" : "\033[38;2;0;255;255m" + keyphrase) << "\033[0m\n";
            cout << "      \033[38;2;255;255;0mLength Range: " << "\033[38;2;0;255;255m" << minLen << " to " << "\033[38;2;0;255;255m" << maxLen << "\033[0m\n";
            cout << "      \033[38;2;255;255;0mTotal combinations: " << "\033[38;2;0;255;255m" << total << "\033[0m\n";
            cout << "      \033[38;2;255;255;0mFile will be saved to: " << "\033[38;2;0;255;255m" << filename << "\033[0m\n";
            cout << "      \033[38;2;255;255;0m----------------------------------------------------------\033[0m\n";
            generatePasswords(charset, "", minLen, maxLen, count, total, 0, outfile);
        }
        
        outfile.close(); // Close the output file after writing
        clearScreen();
        showCursor(); // Show the console cursor after generation
        cout << "\n      \033[38;2;0;255;0m[!] Password generation complete!\033[0m\n";
        cout << "      \033[38;2;255;255;0mTotal passwords generated: " << "\033[38;2;0;255;255m" << count << "\033[0m\n";
        cout << "      \033[38;2;255;255;0mLength: " << "\033[38;2;0;255;255m" << minLen << " to " << "\033[38;2;0;255;255m" << maxLen << "\033[0m\n";
        cout << "      \033[38;2;255;255;0m---------------------------------------------\033[0m\n";
        // Display output filename and keyphrase if present
        cout << "      \033[38;2;255;255;0mOutput written to: " << "\033[38;2;0;255;255m" << filename << "\033[0m\n";
        if(!keyphrase.empty()) {
            cout << "      \033[38;2;255;255;0mKeyphrase used: " << "\033[38;2;0;255;255m" << keyphrase << "\033[0m\n";
        }
        cout << "      \033[38;2;255;255;0mPress any key to return to the main menu...\033[0m\n";
        cin.get(); // Wait for user input before returning to the main menu
        clearScreen(); // Clear the screen before showing the main menu again
    }
}



//┌------------------------------------------------------------------------------┐
//| Interactive charset selection menu.                                          |
//| Lets user toggle character sets and returns the final charset string.        |
//└------------------------------------------------------------------------------┘
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
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    }
    string charset;
    if (upper) charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (lower) charset += "abcdefghijklmnopqrstuvwxyz";
    if (num)   charset += "0123456789";
    if (sym)   charset += "!@#$%^&*()-_=+[]{}|;:',.<>/?";
    return charset;
}

//┌------------------------------------------------------------------------------┐
//| Calculates the total number of possible password combinations.               |
//| Uses charset size and min/max length range with overflow protection.         |
//└------------------------------------------------------------------------------┘
size_t calculateTotal(const string& charset, int minLen, int maxLen, int keyphraseLen) {
    size_t total = 0;
    size_t charsetSize = charset.size();
    
    // Higher cap for password generation - up to 10 billion combinations
    const size_t MAX_REASONABLE_TOTAL = 10000000000ULL; // 10 billion
    
    for (int len = minLen; len <= maxLen; ++len) {
        int charsNeeded = len - keyphraseLen;
        if (charsNeeded <= 0) continue; // Skip if keyphrase is longer than current length
        
        size_t combos = 1;
        for (int i = 0; i < charsNeeded; ++i) {
            // Check for potential overflow
            if (combos > MAX_REASONABLE_TOTAL / charsetSize) {
                return MAX_REASONABLE_TOTAL; // Cap at reasonable limit
            }
            combos *= charsetSize;
        }
        total += combos;
        
        // Cap total to prevent display issues while allowing large generations
        if (total > MAX_REASONABLE_TOTAL) {
            return MAX_REASONABLE_TOTAL;
        }
    }
    return total;
}

//┌------------------------------------------------------------------------------┐
//| Resets the console screen color.                                             |
//└------------------------------------------------------------------------------┘
void resetConsoleColor(int) {
    std::cout << "\033[0m";
    exit(0);
}

//┌------------------------------------------------------------------------------┐
//| Safely converts a string to an integer.                                      |
//| Returns -1 if conversion fails.                                              |
//└------------------------------------------------------------------------------┘
int safeStoi(const string& s) {
    try {
        return stoi(s);
    } catch (...) {
        std::cout << "\033[0m"; // Reset color
        return -1;
    }
}



//┌------------------------------------------------------------------------------┐
//| Recursively generates all possible passwords and writes them to outfile.     |
//| Handles custom modes for charset placement.                                  |
//| Displays progress bar during generation.                                     |
//| Different modes include:                                                     |
//| 0: dictionary (no keyphrase)                                                 |
//| 1: prepend (keyphrase at start)                                              |
//| 2: middle (keyphrase in middle)                                              |
//| 3: append (keyphrase at end)                                                 |
//└------------------------------------------------------------------------------┘
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
) { // Base case: if current length + keyphrase length is within bounds
    if (current.length() + keyphrase.length() >= minLen && current.length() + keyphrase.length() <= maxLen) {
        string password;
        
        // Determine how to combine current string with keyphrase based on mode
        if (keyphrase.empty()) {
            password = current; // No keyphrase, just use current
        } else if (mode == 0) {
            password = current; // Dictionary mode, just current
        } else if (mode == 1) { // Prepend mode
            password = keyphrase + current;
        } else if (mode == 2) { // Middle mode: keyphrase in middle of charset
            // Split current charset string in half and put keyphrase in the middle
            size_t mid = current.length() / 2;
            password = current.substr(0, mid) + keyphrase + current.substr(mid);
        } else if (mode == 3) { // Append mode
            password = current + keyphrase;
        }

        // Write the generated password to the output file
        outfile << password << endl; // Write password to file
        outfile.flush(); // Ensure the output is written immediately
        
        // Show current password being generated (overwrite same line)
        cout << "\r      \033[38;2;0;255;0mGenerated: " << "\033[38;2;0;255;255m" << password << " \033[0m";
        cout.flush(); // Flush the output to ensure it appears immediately
        
        ++count; // Increment the count of generated passwords
        if (count % 50 == 0 || count == total) { // Update progress every 50 passwords or at the end
            hideCursor();
            int barWidth = 40;
            float progress = float(count) / total;
            
            // Move to next line for progress bar, then return cursor
            cout << "\n\r      \033[38;2;255;255;0m" << count << " \033[0m/ " << "\033[38;2;0;255;255m" << total << " \033[38;2;0;255;0m[";
            int pos = barWidth * progress;
            for (int j = 0; j < barWidth; ++j) {
                if (j < pos) cout << ">";
                else if (j == pos) cout << "<:>~";
                else cout << " ";
            }
            // Display percentage as float with 2 decimal places
            cout << "] " << fixed << setprecision(2) << (progress * 100.0) << "%\033[0m";
            
            // Move cursor back up to the "Generated:" line for next update
            cout << "\033[A"; // Move cursor up one line
            cout.flush();
        }
    }
    if (current.length() + keyphrase.length() >= maxLen) return;
    for (char c : charset) {
        generatePasswords(charset, keyphrase, minLen, maxLen, count, total, mode, outfile, current + c);
    }
}