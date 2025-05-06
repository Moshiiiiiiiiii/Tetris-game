#include "game.h"
#include <random>//Allows generating random numbers


Game::Game()
{
    grid = Grid();//Initializes the grid member variable of the Game class by creating a new instance of the Grid class. 
    blocks = GetAllBlocks();//•	The blocks vector is used to store all the possible Tetris block types like IBLOCK,JBLOCK,LBLOCK ETC. BASTA LAHAT NG BLOCKKK
    currentBlock = GetRandomBlock();//assigns a randomly selected block to the currentBlock variable.
    nextBlock = GetRandomBlock();//Start a random dropping block
    gameOver = false;// Indicating the game is not over and gameplay can continue.
    score = 0;//This is typically done to reset the player's score at the start of the game or after a game reset.
    InitAudioDevice();// initialize the audio device for playing sounds and music in the application.
   
    music = LoadMusicStream("C:/Users/salon/Downloads/Tetris-game-main/Tetris-game-main/Tetris/Sounds/Weare.mp3");//Background Music While Playing
    PlayMusicStream(music);//Used to start playing a music stream.
    SetMusicVolume(music, 3.0f);

    rotateSound = LoadSound("C:/Users/salon/Downloads/Tetris-game-main/Tetris-game-main/Tetris/Sounds/rotate.mp3");//Sound effect while rotating the block
    clearSound = LoadSound("C:/Users/salon/Downloads/Tetris-game-main/Tetris-game-main/Tetris/Sounds/clear.mp3");//Sound effect when the block clear
}

Game::~Game()//responsible for cleaning up resources when a Game object is destroyed.
{
    UnloadSound(rotateSound);//Unload the sound effect for block rotation
    UnloadSound(clearSound);//Unload the sound effect for clearing rows
    UnloadMusicStream(music);// Unload the background music stream
    CloseAudioDevice();//Close the audio device to release audio resources

}

Block Game::GetRandomBlock()//selecting a random block from the blocks vector and returning it. 
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();// Refill the blocks vector if it's empty
    }
    int randomIndex = rand() % blocks.size();// Generate a random index
    Block block = blocks[randomIndex];// Select the block at the random index
    blocks.erase(blocks.begin() + randomIndex);// Remove the selected block from the vector
    return block;// Return the selected block
}

// Returns a vector containing all possible Tetris block types
std::vector<Block> Game::GetAllBlocks()
{
    return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };// All block types
}

// Draws the game grid, current block, and next block
void Game::Draw()
{
    grid.Draw();// Draws the game grid
    currentBlock.Draw(11, 11);// Draws the current block at a fixed position
    switch (nextBlock.id)// Draws the next block based on its ID
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
        break;
    }
}

void Game::Reset()
{
    grid = Grid(); // Reset the grid
    blocks = GetAllBlocks(); // Refill the blocks vector
    currentBlock = GetRandomBlock(); // Reset the current block
    nextBlock = GetRandomBlock(); // Reset the next block
    gameOver = false; // Reset the game over state
    score = 0; // Reset the score
}




// Handles player input for controlling the game
void Game::HandleInput()
{
    int keyPressed = GetKeyPressed(); // Get the key pressed by the player
    if (gameOver && keyPressed != 0) // If the game is over and any key is pressed
    {
        gameOver = false; // Reset the game state
 
    }
    switch (keyPressed) // Handle specific key presses
    {
    case KEY_A:
        MoveBlockLeft(); // Move the current block left
        break;
    case KEY_D:
        MoveBlockRight(); // Move the current block right
        break;
    case KEY_S:
        MoveBlockDown(); // Move the current block down
        break;
    case KEY_W:
        RotateBlock(); // Rotate the current block
        break;
    case KEY_SPACE:
        Dropblock();//Drops the blocks automatically
        break;
    case KEY_LEFT:
        MoveBlockLeft(); // Move the current block left
        break;
    case KEY_RIGHT:
        MoveBlockRight(); // Move the current block right
        break;
    case KEY_DOWN:
        MoveBlockDown(); // Move the current block down
        break;
    case KEY_UP:
        RotateBlock(); // Rotate the current block
        break;
   
 
    }
}

// Drops the current block to the lowest possible position
void Game::Dropblock()
{
    while (!gameOver) // Keep moving the block down until it locks
    {
        currentBlock.Move(1, 0); // Move the block down
        if (IsBlockOutside() || BlockFits() == false) // If the block is outside the grid or doesn't fit
        {
            currentBlock.Move(-1, 0); // Undo the last move
            LockBlock(); // Lock the block into the grid
            break; // Exit the loop
        }
    }
}


// Moves the current block left
void Game::MoveBlockLeft()
{
    if (!gameOver)// Only allow movement if the game is not over
    {
        currentBlock.Move(0, -1);// Move the block left
        if (IsBlockOutside() || BlockFits() == false)// If the block is outside the grid or doesn't fit
        {
            currentBlock.Move(0, 1);// Undo the movement
        }
    }
}

// Moves the current block right
void Game::MoveBlockRight()
{
    if (!gameOver)// Only allow movement if the game is not over
    {
        currentBlock.Move(0, 1); // Move the block right
        if (IsBlockOutside() || BlockFits() == false)// If the block is outside the grid or doesn't fit
        {
            currentBlock.Move(0, -1);// Undo the movement
        }
    }
}

// Moves the current block down
void Game::MoveBlockDown()
{
    if (!gameOver)// Only allow movement if the game is not over
    {
        currentBlock.Move(1, 0);// Move the block down
        if (IsBlockOutside() || BlockFits() == false)// If the block is outside the grid or doesn't fit
        {
            currentBlock.Move(-1, 0);// Undo the movement
            LockBlock();// Lock the block into the grid
        }
    }
}



// Checks if the current block is outside the grid
bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();// Get the positions of the block's cells
    for (Position item : tiles)// Iterate through each cell
    {
        if (grid.IsCellOutside(item.row, item.column))// Check if the cell is outside the grid
        {
            return true;// Block is outside
        }
    }
    return false;// Block is inside
}

// Rotates the current block
void Game::RotateBlock()
{
    if (!gameOver) // Only allow rotation if the game is not over
    {
        currentBlock.Rotate();// Rotate the block
        if (IsBlockOutside() || BlockFits() == false)// If the block is outside the grid or doesn't fit
        {
            currentBlock.UndoRotation();// Undo the rotation
        }
        else
        {
            PlaySound(rotateSound);// Play the rotation sound effect
        }
    }
}



// Locks the current block into the grid and spawns the next block
void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();// Get the positions of the block's cells
    for (Position item : tiles)// Iterate through each cell
    {
        grid.grid[item.row][item.column] = currentBlock.id;// Lock the cell into the grid
    }
    currentBlock = nextBlock;// Set the next block as the current block
    if (BlockFits() == false)// If the new block doesn't fit
    {
        gameOver = true;// End the game
    }
    nextBlock = GetRandomBlock();// Spawn a new random block
    int rowsCleared = grid.ClearFullRows();// Clear any full rows
    if (rowsCleared > 0)// If rows were cleared
    {
        PlaySound(clearSound);// Play the row clear sound effect
        UpdateScore(rowsCleared, 0); // Update the score based on the rows cleared
   
    }
}

// Checks if the current block fits in the grid
bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();// Get the positions of the block's cells
    for (Position item : tiles)// Iterate through each cell
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)// If the cell is not empty
        {
            return false; // Block doesn't fit
        }
    }
    return true;// Block fits
}
// Updates the player's score
void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)// Add points based on the number of lines cleared
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += moveDownPoints;// Add points for moving the block down
}
