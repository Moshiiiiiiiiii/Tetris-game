#pragma once // Ensures the header file is included only once during compilation

// The Position class represents a 2D coordinate (row, column) on the Tetris grid
class Position
{
public:
    // Constructor: Initializes a Position object with the given row and column
    Position(int row, int column);

    int row;    // The row index of the position on the grid
    int column; // The column index of the position on the grid
};