//┌--------------------------------------------------------------------------------------------------------┐
//| Flipkit/source/osdetect.h                                                                              |
//| Last Updated: 7/19/2025                                                                                |
//| License: GNU General Public License v3.0                                                               |
//| Description: Provides cross-platform OS detection macros and utility functions for Flipkit.            |
//|              Includes clearScreen and sleepFor for Windows, Linux, and Mac compatibility.              |
//|              Designed for use throughout the toolkit for platform-specific operations.                 |
//└--------------------------------------------------------------------------------------------------------┘
#pragma once
#include <cstdlib> // For system()
#include <iostream>
#include <unistd.h> // For usleep on Linux/Mac
#include <windows.h> // For Sleep on Windows

//Function Prototypes
inline void clearScreen();
inline void sleepFor(int);

// OS detection macros
#if defined(_WIN32)
    #define IS_WINDOWS 1
#else
    #define IS_WINDOWS 0
#endif
// Define macros for Linux and Mac
#if defined(__linux__)
    #define IS_LINUX 1
#else
    #define IS_LINUX 0
#endif
// Define macros for Mac
#if defined(__APPLE__)
    #define IS_MAC 1
#else
    #define IS_MAC 0
#endif

// Cross-platform clearScreen function
inline void clearScreen() {
#if IS_WINDOWS
    system("cls");
#elif IS_LINUX || IS_MAC
    system("clear");
#endif
}
// Cross-platform sleep function
inline void sleepFor(int milliseconds) {
    if(IS_WINDOWS) {
        Sleep(milliseconds); // Windows Sleep function
    } else if (IS_LINUX || IS_MAC) {
        usleep(milliseconds * 1000); // usleep takes microseconds, so multiply by 1000
    }

    else {
        sleep(milliseconds / 1000); // Fallback for unknown OS
    }
}