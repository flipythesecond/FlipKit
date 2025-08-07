//┌--------------------------------------------------------------------------------------------------------┐
//| Flipkit/source/asciiart.h                                                                              |
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
    clearScreen(); // Clear once at the beginning
    
    // Move cursor to top-left and overwrite frames
    std::cout << "\033[H"; // Move cursor to home position (1,1)
    printFliplistAsciiArt5();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    std::cout << "\033[H"; // Move cursor to home position
    printFliplistAsciiArt4();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    std::cout << "\033[H";
    printFliplistAsciiArt3();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    std::cout << "\033[H";
    printFliplistAsciiArt2();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    std::cout << "\033[H";
    printFliplistAsciiArt1();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    // Continue animation sequence
    std::cout << "\033[H";
    printFliplistAsciiArt2();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    std::cout << "\033[H";
    printFliplistAsciiArt3();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    std::cout << "\033[H";
    printFliplistAsciiArt4();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    // Final frame sequence
    std::cout << "\033[H";
    printFliplistAsciiArt5();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(2500000);
    
     std::cout << "\033[H"; // Move cursor to home position
    printFliplistAsciiArt4();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    std::cout << "\033[H";
    printFliplistAsciiArt3();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    std::cout << "\033[H";
    printFliplistAsciiArt2();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    std::cout << "\033[H";
    printFliplistAsciiArt1();
    std::cout.flush();
    if(IS_WINDOWS) Sleep(200); else usleep(200000);
    
    clearScreen(); // Clear once at the end
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
    std::cout << std::endl;
    // Centered "By Flipy" with colored "By" and "Flipy"
    std::cout << std::string(32, ' '); // Adjust spaces for center alignment
    std::cout << "      \033[38;2;255;165;0mBy\033[0m "; // Orange/Yellow "By"
    std::cout << "\033[38;2;0;255;255mFlipy ...| \033[0m\n"; // Light blue "Flipy"
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
    std::cout << std::endl;
    // Centered "By Flipy" with colored "By" and "Flipy"
    std::cout << std::string(32, ' '); // Adjust spaces for center alignment
    std::cout << "      \033[38;2;255;165;0mBy\033[0m "; // Orange/Yellow "By"
    std::cout << "\033[38;2;0;255;255mFlipy ...\\ \033[0m\n"; // Light blue "Flipy"
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
    std::cout << std::endl;
    // Centered "By Flipy" with colored "By" and "Flipy"
    std::cout << std::string(32, ' '); // Adjust spaces for center alignment
    std::cout << "      \033[38;2;255;165;0mBy\033[0m "; // Orange/Yellow "By"
    std::cout << "\033[38;2;0;255;255mFlipy ..- \033[0m\n"; // Light blue "Flipy"
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
    std::cout << std::endl;
    // Centered "By Flipy" with colored "By" and "Flipy"
    std::cout << std::string(32, ' '); // Adjust spaces for center alignment
    std::cout << "      \033[38;2;255;165;0mBy\033[0m "; // Orange/Yellow "By"
    std::cout << "\033[38;2;0;255;255mFlipy ./ \033[0m\n"; // Light blue "Flipy"
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
    std::cout << std::endl;
    // Centered "By Flipy" with colored "By" and "Flipy"
    std::cout << std::string(32, ' '); // Adjust spaces for center alignment
    std::cout << "      \033[38;2;255;165;0mBy\033[0m "; // Orange/Yellow "By"
    std::cout << "\033[38;2;0;255;255mFlipy | \033[0m\n"; // Light blue "Flipy"
}
#endif // ASCIIART_H

