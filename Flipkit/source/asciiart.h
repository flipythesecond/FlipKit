//┌--------------------------------------------------------------------------------------------------------┐
//| Flipkit/source/asciiart.h                                                                              |
//| Author: Bek A.                                                                                         |
//| Last Updated: 7/19/2025                                                                                |
//| License: GNU General Public License v3.0                                                               |
//| Description: This header provides animated ASCII art for the Fliplist tool.                            |
//|              It contains functions for displaying Fliplist's startup animation frames.                 |
//|              Intended for use as a visual introduction in the Flipkit toolkit.                         |
//└--------------------------------------------------------------------------------------------------------┘
#ifndef ASCIIART_H
#define ASCIIART_H 
#include <iostream>
#include <string>
#include <windows.h> // For Sleep function
#include <cstdlib> // For system function
#include "osdetect.h" // For OS detection macros

// Function Prototypes

inline void printFliplistAsciiArt();
inline void printFliplistAsciiArt1();
inline void printFliplistAsciiArt2();
inline void printFliplistAsciiArt3();
inline void printFliplistAsciiArt4();
inline void printFliplistAsciiArt5();

// Function to display the FlipKit ASCII art animation


//


// Animated ASCII Art for Fliplist
inline void printFliplistAsciiArt() {
    clearScreen(); // Clear the screen before printing the first art
    printFliplistAsciiArt1();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the next art
    printFliplistAsciiArt2();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the next art
    printFliplistAsciiArt3();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen after the last art
    printFliplistAsciiArt4();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen after the last art
    printFliplistAsciiArt5();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the first art
    printFliplistAsciiArt4();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the next art
    printFliplistAsciiArt3();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the next art
    printFliplistAsciiArt2();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen after the last art
    printFliplistAsciiArt1();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen after the last art
    printFliplistAsciiArt2();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the next art
    printFliplistAsciiArt3();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the next art
    printFliplistAsciiArt4();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the next art
    printFliplistAsciiArt5();
    clearScreen(); // Clear the screen after the last art
    printFliplistAsciiArt4();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the next art
    printFliplistAsciiArt3();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the next art
    printFliplistAsciiArt2();
    Sleep(250); // Pause for 250 milliseconds
    clearScreen(); // Clear the screen before printing the next art
    printFliplistAsciiArt1();
    Sleep(2500); // Pause for 2500 milliseconds
    clearScreen(); // Clear the screen after the last art

}

// First Frame of ASCII Art
inline void printFliplistAsciiArt1() {
    // Green color: \033[38;2;0;255;0m, Reset: \033[0m
    std::cout << "\033[38;2;0;255;0m";
    std::cout << " _________   __           __   ________   __           __      __________       ____________" << std::endl;
    std::cout << "|   ______| |  |         |  | |   __   | |  |         |  |    /        * | __y |____    ____|  " << std::endl;
    std::cout << "|  |        |  |         |  | |  |__|  | |  |         |  |   /  ---------\\/         |  |     " << std::endl;
    std::cout << "|  |_____   |  |         |  | |   _____| |  |         |  |  /  /                    |  |      " << std::endl;
    std::cout << "|   _____|  |  |         |  | |  |       |  |         |  |  \\  \\______              |  |     " << std::endl;
    std::cout << "|  |        |  |         |  | |  |       |  |         |  |   \\_____   |             |  |  " << std::endl;
    std::cout << "|  |        |  |_______  |  | |  |       |  |_______  |  |    _____|  |             |  |    " << std::endl;
    std::cout << "|__|        |__________| |__| |__|       |__________| |__|   |________|             |__|       " << std::endl;
    std::cout << "\033[0m"; // Reset color
}
// First Frame of ASCII Art
inline void printFliplistAsciiArt2() {
    // Green color: \033[38;2;0;255;0m, Reset: \033[0m
    std::cout << "\033[38;2;0;255;0m";
    std::cout << " _________   __           __   ________   __           __      __________       ____________" << std::endl;
    std::cout << "|   ______| |  |         |  | |   __   | |  |         |  |    /        * | _y  |____    ____|  " << std::endl;
    std::cout << "|  |        |  |         |  | |  |__|  | |  |         |  |   /  ---------\\/         |  |     " << std::endl;
    std::cout << "|  |_____   |  |         |  | |   _____| |  |         |  |  /  /                    |  |      " << std::endl;
    std::cout << "|   _____|  |  |         |  | |  |       |  |         |  |  \\  \\______              |  |     " << std::endl;
    std::cout << "|  |        |  |         |  | |  |       |  |         |  |   \\_____   |             |  |  " << std::endl;
    std::cout << "|  |        |  |_______  |  | |  |       |  |_______  |  |    _____|  |             |  |    " << std::endl;
    std::cout << "|__|        |__________| |__| |__|       |__________| |__|   |________|             |__|       " << std::endl;
    std::cout << "\033[0m"; // Reset color
}

// Second Frame of ASCII Art
inline void printFliplistAsciiArt3() {
    // Green color: \033[38;2;0;255;0m, Reset: \033[0m
    std::cout << "\033[38;2;0;255;0m";
    std::cout << " _________   __           __   ________   __           __      __________       ____________" << std::endl;
    std::cout << "|   ______| |  |         |  | |   __   | |  |         |  |    /        * | y   |____    ____|  " << std::endl;
    std::cout << "|  |        |  |         |  | |  |__|  | |  |         |  |   /  ---------\\/         |  |     " << std::endl;
    std::cout << "|  |_____   |  |         |  | |   _____| |  |         |  |  /  /                    |  |      " << std::endl;
    std::cout << "|   _____|  |  |         |  | |  |       |  |         |  |  \\  \\______              |  |     " << std::endl;
    std::cout << "|  |        |  |         |  | |  |       |  |         |  |   \\_____   |             |  |  " << std::endl;
    std::cout << "|  |        |  |_______  |  | |  |       |  |_______  |  |    _____|  |             |  |    " << std::endl;
    std::cout << "|__|        |__________| |__| |__|       |__________| |__|   |________|             |__|       " << std::endl;
    std::cout << "\033[0m"; // Reset color
}

// Third Frame of ASCII Art
inline void printFliplistAsciiArt4() {
        // Green color: \033[38;2;0;255;0m, Reset: \033[0m
    std::cout << "\033[38;2;0;255;0m";
    std::cout << " _________   __           __   ________   __           __      __________       ____________" << std::endl;
    std::cout << "|   ______| |  |         |  | |   __   | |  |         |  |    /        * |     |____    ____|  " << std::endl;
    std::cout << "|  |        |  |         |  | |  |__|  | |  |         |  |   /  ---------\\y         |  |     " << std::endl;
    std::cout << "|  |_____   |  |         |  | |   _____| |  |         |  |  /  /                    |  |      " << std::endl;
    std::cout << "|   _____|  |  |         |  | |  |       |  |         |  |  \\  \\______              |  |     " << std::endl;
    std::cout << "|  |        |  |         |  | |  |       |  |         |  |   \\_____   |             |  |  " << std::endl;
    std::cout << "|  |        |  |_______  |  | |  |       |  |_______  |  |    _____|  |             |  |    " << std::endl;
    std::cout << "|__|        |__________| |__| |__|       |__________| |__|   |________|             |__|       " << std::endl;
    std::cout << "\033[0m"; // Reset color
}

// Last Frame of ASCII Art
inline void printFliplistAsciiArt5() {
    // Green color: \033[38;2;0;255;0m, Reset: \033[0m
    std::cout << "\033[38;2;0;255;0m";
    std::cout << " _________   __           __   ________   __           __      __________       ____________" << std::endl;
    std::cout << "|   ______| |  |         |  | |   __   | |  |         |  |    /        * |     |____    ____|  " << std::endl;
    std::cout << "|  |        |  |         |  | |  |__|  | |  |         |  |   /  ---------           |  |     " << std::endl;
    std::cout << "|  |_____   |  |         |  | |   _____| |  |         |  |  /  /                    |  |      " << std::endl;
    std::cout << "|   _____|  |  |         |  | |  |       |  |         |  |  \\  \\______              |  |     " << std::endl;
    std::cout << "|  |        |  |         |  | |  |       |  |         |  |   \\_____   |             |  |  " << std::endl;
    std::cout << "|  |        |  |_______  |  | |  |       |  |_______  |  |    _____|  |             |  |    " << std::endl;
    std::cout << "|__|        |__________| |__| |__|       |__________| |__|   |________|             |__|       " << std::endl;
    std::cout << "\033[0m"; // Reset color
}
#endif // ASCIIART_H

