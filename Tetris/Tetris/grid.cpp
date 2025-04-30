#include "grid.h" // Includes the header file for the Grid class
#include <iostream> // Includes the iostream library for printing the grid to the console
#include "colors.h" // Includes the colors for rendering the grid cells

// Constructor: Initializes the grid with default values
Grid::Grid()
{
    numRows = 20; // Number of rows in the grid
    numCols = 10; // Number of columns in the grid
    cellSize = 30; // Size of each cell in the grid (e.g., 30x30 pixels)
    Initialize(); // Initializes the grid with empty cells
    colors = GetCellColors(); // Retrieves the predefined colors for rendering cells
}

// Initializes the grid by setting all cells to 0 (empty)
void Grid::Initialize()
{
    for (int row = 0; row < numRows; row++) // Iterate through each row
    {
        for (int column = 0; column < numCols; column++) // Iterate through each column
        {
            grid[row][column] = 0; // Set the cell to 0 (empty)
        }
    }
}

// Prints the grid to the console (for debugging purposes)
void Grid::Print()
{
    for (int row = 0; row < numRows; row++) // Iterate through each row
    {
        for (int column = 0; column < numCols; column++) // Iterate through each column
        {
            std::cout << grid[row][column] << " "; // Print the cell value
        }
        std::cout << std::endl; // Move to the next line after each row
    }
}

// Draws the grid on the screen
void Grid::Draw()
{
    for (int row = 0; row < numRows; row++) // Iterate through each row
    {
        for (int column = 0; column < numCols; column++) // Iterate through each column
        {
            int cellValue = grid[row][column]; // Get the value of the cell
            // Draw the cell as a rectangle with the corresponding color
            DrawRectangle(
                column * cellSize + 11, // X-coordinate of the rectangle
                row * cellSize + 11,    // Y-coordinate of the rectangle
                cellSize - 1,           // Width of the rectangle (slightly smaller for spacing)
                cellSize - 1,           // Height of the rectangle (slightly smaller for spacing)
                colors[cellValue]       // Color of the rectangle based on the cell value
            );
        }
    }
}

// Checks if a cell is outside the grid boundaries
bool Grid::IsCellOutside(int row, int column)
{
    if (row >= 0 && row < numRows && column >= 0 && column < numCols) // Check if the cell is within bounds
    {
        return false; // The cell is inside the grid
    }
    return true; // The cell is outside the grid
}

// Checks if a cell is empty (value is 0)
bool Grid::IsCellEmpty(int row, int column)
{
    if (grid[row][column] == 0) // Check if the cell value is 0
    {
        return true; // The cell is empty
    }
    return false; // The cell is not empty
}

// Clears full rows and moves rows above them down
int Grid::ClearFullRows()
{
    int completed = 0; // Tracks the number of rows cleared
    for (int row = numRows - 1; row >= 0; row--) // Iterate from the bottom row to the top
    {
        if (IsRowFull(row)) // Check if the row is full
        {
            ClearRow(row); // Clear the full row
            completed++; // Increment the count of cleared rows
        }
        else if (completed > 0) // If rows have been cleared below
        {
            MoveRowDown(row, completed); // Move the current row down by the number of cleared rows
        }
    }
    return completed; // Return the number of rows cleared
}

// Checks if a row is full (no empty cells)
bool Grid::IsRowFull(int row)
{
    for (int column = 0; column < numCols; column++) // Iterate through each column in the row
    {
        if (grid[row][column] == 0) // Check if the cell is empty
        {
            return false; // The row is not full
        }
    }
    return true; // The row is full
}

// Clears a specific row by setting all its cells to 0 (empty)
void Grid::ClearRow(int row)
{
    for (int column = 0; column < numCols; column++) // Iterate through each column in the row
    {
        grid[row][column] = 0; // Set the cell to 0 (empty)
    }
}

// Moves a row down by a specified number of rows
void Grid::MoveRowDown(int row, int numRows)
{
    for (int column = 0; column < numCols; column++) // Iterate through each column in the row
    {
        grid[row + numRows][column] = grid[row][column]; // Move the cell value down
        grid[row][column] = 0; // Clear the original cell
    }
}

