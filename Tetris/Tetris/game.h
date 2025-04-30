#pragma once// Ensures the header file is included only once during compilation
#include "grid.h"// Includes the Grid class, which represents the Tetris game board
#include "blocks.cpp"// Includes the implementation of blocks (Tetris pieces)

// The Game class manages the overall game logic, state, and resources
class Game
{
public://public means access to all items
    Game(); // Constructor: Initializes the game state and resources
    ~Game();// Destructor: Cleans up resources when the game ends
    void Draw();// Draws the game grid, current block, and next block
    void HandleInput();// Handles player input for controlling the game
    void MoveBlockDown();// Moves the current block down
    void Dropblock();//Drop fast the block
    bool gameOver;// Tracks whether the game is over
    int score;// Stores the player's score
    Music music;// Background music for the game

private://private means you can't use to other items
    void MoveBlockLeft();// Moves the current block to the left
    void MoveBlockRight();// Moves the current block to the right
    Block GetRandomBlock();// Selects and returns a random block
    std::vector<Block> GetAllBlocks();// Returns a vector of all possible Tetris blocks
    bool IsBlockOutside();// Checks if the current block is outside the grid
    void RotateBlock(); // Rotates the current block
    void LockBlock();// Locks the current block into the grid and spawns the next block
    bool BlockFits();// Checks if the current block fits in the grid
    void Reset();// Resets the game state
    void UpdateScore(int linesCleared, int moveDownPoints);// Updates the player's score
    Grid grid;// Represents the Tetris game board
    std::vector<Block> blocks;// Stores all available Tetris blocks
    Block currentBlock;// The block currently being controlled by the player
    Block nextBlock; // The next block to be dropped
    Sound rotateSound;// Sound effect for rotating the block
    Sound clearSound;// Sound effect for clearing rows
};
