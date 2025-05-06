#pragma once // Ensures the header file is included only once during compilation
#include <vector>   // Includes the vector container for managing collections of colors
#include <raylib.h> // Includes the raylib library for rendering and the Color struct

// The Grid class represents the Tetris game board and manages its state and behavior
class Grid
{
public:
    Grid(); // Constructor: Initializes the grid with default values

    // Resets the grid by setting all cells to empty (value 0)
    void Initialize();

    // Prints the grid to the console (useful for debugging)
    void Print();

    // Draws the grid on the screen, rendering each cell with its corresponding color
    void Draw();

    // Checks if a specific cell is outside the grid boundaries
    bool IsCellOutside(int row, int column);

    // Checks if a specific cell is empty (value 0)
    bool IsCellEmpty(int row, int column);

    // Clears all full rows in the grid and returns the number of rows cleared
    int ClearFullRows();

    // 2D array representing the grid, where each cell contains an integer value
    // 0 indicates an empty cell, and other values correspond to block IDs
    int grid[20][10];

private:
    // Checks if a specific row is full (no empty cells)
    bool IsRowFull(int row);

    // Clears a specific row by setting all its cells to 0 (empty)
    void ClearRow(int row);

    // Moves a row down by a specified number of rows
    void MoveRowDown(int row, int numRows);

    int numRows; // Number of rows in the grid
    int numCols; // Number of columns in the grid
    int cellSize; // Size of each cell in the grid (e.g., 30x30 pixels)
    std::vector<Color> colors; // Vector of colors used to render the grid cells
};


