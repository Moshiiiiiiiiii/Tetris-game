#include "colors.h" // Includes the header file for color definitions and declarations

// Define various colors using the Color struct (R, G, B, A format)
// Each color is represented by its red, green, blue, and alpha (opacity) components

const Color black = { 0, 0, 0, 255 };   // A dark gray color, likely used for the grid or background
const Color green = { 47, 230, 23, 255 };     // A bright green color, possibly for the SBlock
const Color red = { 232, 18, 18, 255 };       // A bright red color, possibly for the ZBlock
const Color orange = { 226, 116, 17, 255 };   // An orange color, possibly for the LBlock
const Color yellow = { 237, 234, 4, 255 };    // A yellow color, possibly for the OBlock
const Color purple = { 166, 0, 247, 255 };    // A purple color, possibly for the TBlock
const Color cyan = { 21, 204, 209, 255 };     // A cyan color, possibly for the IBlock
const Color blue = { 13, 64, 216, 255 };      // A blue color, possibly for the JBlock
const Color lightBlue = { 59, 85, 162, 255 }; // A lighter blue, likely used for UI elements or highlights
const Color darkBlue = { 44, 44, 127, 255 };  // A dark blue, possibly used for the background

// Returns a vector of colors for use in the game, likely for coloring Tetris blocks
std::vector<Color> GetCellColors()
{
    // The order of colors in this vector may correspond to block types (e.g., LBlock, JBlock, etc.)
    return { black, green, red, orange, yellow, purple, cyan, blue };
}