#pragma once // Ensures the header file is included only once during compilation

#include <raylib.h> // Includes the raylib library for the Color struct and related functionality
#include <vector>   // Includes the vector container for managing collections of colors

// Extern declarations for color constants, defined in colors.cpp
// These colors are used throughout the game for blocks, grid, and UI elements
extern const Color darkGrey;   // A dark gray color, likely used for the grid or background
extern const Color green;      // A bright green color, possibly for the SBlock
extern const Color red;        // A bright red color, possibly for the ZBlock
extern const Color orange;     // An orange color, possibly for the LBlock
extern const Color yellow;     // A yellow color, possibly for the OBlock
extern const Color purple;     // A purple color, possibly for the TBlock
extern const Color cyan;       // A cyan color, possibly for the IBlock
extern const Color blue;       // A blue color, possibly for the JBlock
extern const Color lightBlue;  // A lighter blue, likely used for UI elements or highlights
extern const Color darkBlue;   // A dark blue, possibly used for the background

// Function declaration for retrieving a collection of colors
// Returns a vector of colors, likely used for assigning colors to Tetris blocks
std::vector<Color> GetCellColors();