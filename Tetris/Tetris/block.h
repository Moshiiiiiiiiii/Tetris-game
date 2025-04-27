#pragma once // Ensures the header file is included only once during compilation

#include <vector> // Includes the vector container for managing collections of positions and colors
#include <map>    // Includes the map container for managing rotation states and their corresponding cell positions
#include "position.h" // Includes the Position class for defining cell positions
#include "colors.h"   // Includes the Color struct for managing block colors

// The Block class represents a Tetris block and its behavior
class Block
{
public:
    Block(); // Constructor: Initializes a Block object

    // Draws the block on the screen at the specified offset
    void Draw(int offsetX, int offsetY);

    // Moves the block by the specified number of rows and columns
    void Move(int rows, int columns);

    // Returns the current positions of the block's cells on the grid
    std::vector<Position> GetCellPositions();

    // Rotates the block to the next rotation state
    void Rotate();

    // Undoes the last rotation, returning the block to its previous state
    void UndoRotation();

    int id; // Unique identifier for the block type (e.g., LBlock, JBlock, etc.)

    // Maps rotation states (0, 1, 2, 3) to the corresponding cell positions
    std::map<int, std::vector<Position>> cells;

private:
    int cellSize; // The size of each cell in the block (e.g., width and height in pixels)
    int rotationState; // The current rotation state of the block (0, 1, 2, or 3)
    std::vector<Color> colors; // The colors associated with the block
    int rowOffset; // The block's vertical offset on the grid
    int columnOffset; // The block's horizontal offset on the grid
};


