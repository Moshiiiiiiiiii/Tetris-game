#include "block.h" // Includes the header file for the Block class

// Constructor: Initializes a Block object with default values
Block::Block()
{
    cellSize = 30; // Sets the size of each cell in the block (e.g., 30x30 pixels)
    rotationState = 0; // Initializes the block's rotation state to 0 (default orientation)
    colors = GetCellColors(); // Retrieves the predefined colors for blocks
    rowOffset = 0; // Sets the initial vertical offset of the block on the grid
    columnOffset = 0; // Sets the initial horizontal offset of the block on the grid
}

// Draws the block on the screen at the specified offset
void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions(); // Gets the current positions of the block's cells
    for (Position item : tiles) // Iterates through each cell in the block
    {
        // Draws a rectangle for each cell at its calculated position
        DrawRectangle(
            item.column * cellSize + offsetX, // X-coordinate of the rectangle
            item.row * cellSize + offsetY,   // Y-coordinate of the rectangle
            cellSize - 1,                    // Width of the rectangle (slightly smaller for spacing)
            cellSize - 1,                    // Height of the rectangle (slightly smaller for spacing)
            colors[id]                       // Color of the rectangle based on the block's ID
        );
    }
}

// Moves the block by the specified number of rows and columns
void Block::Move(int rows, int columns)
{
    rowOffset += rows; // Adjusts the vertical offset by the specified number of rows
    columnOffset += columns; // Adjusts the horizontal offset by the specified number of columns
}

// Returns the current positions of the block's cells on the grid
std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState]; // Gets the cell positions for the current rotation state
    std::vector<Position> movedTiles; // Stores the adjusted positions of the cells
    for (Position item : tiles) // Iterates through each cell in the block
    {
        // Adjusts the cell's position based on the block's offsets
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos); // Adds the adjusted position to the list
    }
    return movedTiles; // Returns the adjusted positions of the block's cells
}

// Rotates the block to the next rotation state
void Block::Rotate()
{
    rotationState++; // Advances to the next rotation state
    if (rotationState == (int)cells.size()) // If the rotation state exceeds the number of states
    {
        rotationState = 0; // Wraps around to the first rotation state
    }
}

// Undoes the last rotation, returning the block to its previous state
void Block::UndoRotation()
{
    rotationState--; // Reverts to the previous rotation state
    if (rotationState == -1) // If the rotation state goes below 0
    {
        rotationState = cells.size() - 1; // Wraps around to the last rotation state
    }
}
