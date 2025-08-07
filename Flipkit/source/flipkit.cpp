//┌-------------------------------------------------------------------------------------------------------┐
//| Flipkit/source/flipkit.cpp                                                                            |
//| Last Updated: 7/19/2025                                                                               |
//| License: GNU General Public License v3.0                                                              |
//| Description: Main file for the Flipkit toolkit.                                                       |
//|              Displays license and introduction, then branches to available modules and tools.         |
//|              Designed for extensibility; more features and utilities will be added over time.         |
//└-------------------------------------------------------------------------------------------------------┘
#include <iostream>
#include "asciiart.h"
#include "osdetect.h"
#include "gpl_license.h"
#include "fliplist.cpp"
#include "cursor.h" // For hideCursor and showCursor functions

using namespace std;


int main() {

    // Display the GPLv3 license notice at the start of the program
    displayGPLv3Notice(); // Function already has clearScreen() call

    //Ascci Art Introduction Animation
 






    return 0;
}