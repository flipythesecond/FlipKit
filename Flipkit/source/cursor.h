//┌--------------------------------------------------------------------------------------------------------┐
//| Flipkit/source/cursor.h                                                                                |
//| Last Updated: 7/19/2025                                                                                |
//| License: GNU General Public License v3.0                                                               |
//| Description: This header provides cross-platform functions to hide and show the console cursor.        |
//|              It uses Windows API or ANSI escape codes depending on the operating system.               |
//|              Intended for use in Flipkit tools to improve user interface experience.                   |
//└--------------------------------------------------------------------------------------------------------┘
#ifndef CURSOR_H
#define CURSOR_H

#include <iostream>
#include "osdetect.h"

inline void hideCursor() {
#if IS_WINDOWS
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
#elif IS_LINUX || IS_MAC
    std::cout << "\033[?25l";
    std::cout.flush();
#else
    // Fallback: do nothing
#endif
}

inline void showCursor() {
#if IS_WINDOWS
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
#elif IS_LINUX || IS_MAC
    std::cout << "\033[?25h";
    std::cout.flush();
#else
    // Fallback: do nothing
#endif
}

#endif // CURSOR_H