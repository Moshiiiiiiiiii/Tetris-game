#include "position.h" // Includes the header file for the Position class

// Constructor: Initializes a Position object with the given row and column values
Position::Position(int row, int column)
{
    this->row = row;       // Assigns the provided row value to the row member variable
    this->column = column; // Assigns the provided column value to the column member variable
}