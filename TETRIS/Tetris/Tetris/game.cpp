#include "game.h"
#include <random> // Allows generating random numbers
#include <iostream> // For logging drop positions

Game::Game()
{
    grid = Grid(); // Initializes the grid member variable of the Game class
    blocks = GetAllBlocks(); // The blocks vector is used to store all the possible Tetris block types
    currentBlock = GetRandomBlock(); // Assigns a randomly selected block to the currentBlock variable
    nextBlock = GetRandomBlock(); // Start a random dropping block
    gameOver = false; // Indicating the game is not over and gameplay can continue
    score = 0; // This is typically done to reset the player's score at the start of the game or after a game reset
    InitAudioDevice(); // Initialize the audio device for playing sounds and music in the application

    music = LoadMusicStream("C:/Users/SNY IT Solutions/Downloads/Tetris-game-main/Tetris-game-main/Tetris-game-main/Tetris/Sounds/Weare.mp3"); // Background Music While Playing
    PlayMusicStream(music); // Used to start playing a music stream
    SetMusicVolume(music, 3.0f);

    rotateSound = LoadSound("C:/Users/SNY IT Solutions/Downloads/Tetris-game-main/Tetris-game-main/Tetris-game-main/Tetris/Sounds/rotate.mp3"); // Sound effect while rotating the block
    clearSound = LoadSound("C:/Users/SNY IT Solutions/Downloads/Tetris-game-main/Tetris-game-main/Tetris-game-main/Tetris/Sounds/clear.mp3"); // Sound effect when the block clears
}
std::vector<Position> Game::CalculateGhostPosition()
{
    Block tempBlock = currentBlock; // Create a temporary block to simulate the drop
    while (true)
    {
        tempBlock.Move(1, 0); // Move the block down
        if (IsBlockOutside() || !BlockFits()) // Stop if the block is outside or doesn't fit
        {
            tempBlock.Move(-1, 0); // Undo the last move
            break;
        }
    }
    return tempBlock.GetCellPositions(); // Return the final positions of the ghost piece
}

Game::~Game()
{
    UnloadSound(rotateSound); // Unload the sound effect for block rotation
    UnloadSound(clearSound); // Unload the sound effect for clearing rows
    UnloadMusicStream(music); // Unload the background music stream
    CloseAudioDevice(); // Close the audio device to release audio resources
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks(); // Refill the blocks vector if it's empty
    }
    int randomIndex = rand() % blocks.size(); // Generate a random index
    Block block = blocks[randomIndex]; // Select the block at the random index
    blocks.erase(blocks.begin() + randomIndex); // Remove the selected block from the vector
    return block; // Return the selected block
}

std::vector<Block> Game::GetAllBlocks()
{
    return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() }; // All block types
}

void Game::SwapNextBlockWithCurrent()
{
    if (!gameOver) // Only allow swapping if the game is not over
    {
        std::swap(currentBlock, nextBlock); // Swap the current block with the next block
    }
}
void DrawRectangleWithStroke(Rectangle rect, Color fillColor, Color strokeColor, float strokeThickness)
{
    // Draw the stroke (outer rectangle)
    DrawRectangle(
        rect.x - strokeThickness, // Adjust position for stroke
        rect.y - strokeThickness,
        rect.width + 2 * strokeThickness, // Increase size for stroke
        rect.height + 2 * strokeThickness,
        strokeColor // Stroke color
    );

    // Draw the inner rectangle (fill)
    DrawRectangle(
        rect.x, // Original position
        rect.y,
        rect.width, // Original size
        rect.height,
        fillColor // Fill color
    );
}


void Game::Draw()
{
    grid.Draw(); // Draw the game grid

    // Draw the current block
    std::vector<Position> blockCells = currentBlock.GetCellPositions();
    for (Position cell : blockCells)
    {
        int x = cell.column * grid.GetCellSize() + 11;
        int y = cell.row * grid.GetCellSize() + 11;

        DrawRectangleWithStroke(
            { static_cast<float>(x), static_cast<float>(y), static_cast<float>(grid.GetCellSize() - 1), static_cast<float>(grid.GetCellSize() - 1) },
            currentBlock.GetColors()[currentBlock.id],
            WHITE,
            2.0f
        );
    }

    // Draw the next block in the "next rectangle" position
    if (nextBlock.id != 0) // Ensure there is a next block to draw
    {
        nextBlock.Draw(320, 215); // Draw the next block at the fixed "next rectangle" position
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
        Dropblock(); // Drops the blocks automatically
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
            case KEY_Z:
        SwapNextBlockWithCurrent(); // Swap the next block with the current block
        break;
    }
}


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

void Game::MoveBlockLeft()
{
    if (!gameOver) // Only allow movement if the game is not over
    {
        currentBlock.Move(0, -1); // Move the block left
        if (IsBlockOutside() || BlockFits() == false) // If the block is outside the grid or doesn't fit
        {
            currentBlock.Move(0, 1); // Undo the movement
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver) // Only allow movement if the game is not over
    {
        currentBlock.Move(0, 1); // Move the block right
        if (IsBlockOutside() || BlockFits() == false) // If the block is outside the grid or doesn't fit
        {
            currentBlock.Move(0, -1); // Undo the movement
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver) // Only allow movement if the game is not over
    {
        currentBlock.Move(1, 0); // Move the block down
        if (IsBlockOutside() || BlockFits() == false) // If the block is outside the grid or doesn't fit
        {
            currentBlock.Move(-1, 0); // Undo the movement
            LockBlock(); // Lock the block into the grid
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions(); // Get the positions of the block's cells
    for (Position item : tiles) // Iterate through each cell
    {
        if (grid.IsCellOutside(item.row, item.column)) // Check if the cell is outside the grid
        {
            return true; // Block is outside
        }
    }
    return false; // Block is inside
}

void Game::RotateBlock()
{
    if (!gameOver) // Only allow rotation if the game is not over
    {
        currentBlock.Rotate(); // Rotate the block
        if (IsBlockOutside() || BlockFits() == false) // If the block is outside the grid or doesn't fit
        {
            currentBlock.UndoRotation(); // Undo the rotation
        }
        else
        {
            PlaySound(rotateSound); // Play the rotation sound effect
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions(); // Get the positions of the block's cells
    for (Position item : tiles) // Iterate through each cell
    {
        grid.grid[item.row][item.column] = currentBlock.id; // Lock the cell into the grid
    }
    currentBlock = nextBlock; // Set the next block as the current block
    if (BlockFits() == false) // If the new block doesn't fit
    {
        gameOver = true; // End the game
    }
    nextBlock = GetRandomBlock(); // Spawn a new random block
    int rowsCleared = grid.ClearFullRows(); // Clear any full rows
    if (rowsCleared > 0) // If rows were cleared
    {
        PlaySound(clearSound); // Play the row clear sound effect
        UpdateScore(rowsCleared, 0); // Update the score based on the rows cleared
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions(); // Get the positions of the block's cells
    for (Position item : tiles) // Iterate through each cell
    {
        if (grid.IsCellEmpty(item.row, item.column) == false) // If the cell is not empty
        {
            return false; // Block doesn't fit
        }
    }
    return true; // Block fits
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared) // Add points based on the number of lines cleared
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

    score += moveDownPoints; // Add points for moving the block down
}
