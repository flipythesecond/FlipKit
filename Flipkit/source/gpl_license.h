//┌-------------------------------------------------------------------------------------------------------┐
//| Flipkit/source/gpl_license.h                                                                          |
//| Last Updated: 7/19/2025                                                                               |
//| License: GNU General Public License v3.0                                                              |
//| Description: Displays the GPLv3 license notice for Flipkit.                                           |
//|              Intended for use at program startup.                                                     |
//|              This header may be expanded or adapted for future toolkit needs.                         |
//└-------------------------------------------------------------------------------------------------------┘
#pragma once
#include <iostream>
#include "osdetect.h"
#include <limits> // For std::numeric_limits

// Function to display the GPLv3 license notice
// This function should be called at the start of the Flipkit program
inline void displayGPLv3Notice() {
    std::cout <<
R"(Flipkit - PenTest Toolkit
Copyright (C) 2025  Bek A.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
)";
    // Wait for user input to continue
    std::cout << "\nPress Enter to continue...";
    // Clear the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Wait for the user to press Enter
    std::cin.clear(); // Clear any error flags
    std::cin.get();
    clearScreen(); // Clear the screen after displaying the notice
}
