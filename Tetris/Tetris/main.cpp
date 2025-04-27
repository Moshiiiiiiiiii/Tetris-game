#include <raylib.h> // Includes the raylib library for rendering and game utilities
#include "game.h"   // Includes the Game class for managing game logic
#include "colors.h" // Includes color definitions for rendering
#include <iostream> // Includes the iostream library for debugging (if needed)

// Global variable to track the last update time for timed events
double lastUpdateTime = 0;

// Function to check if a specific time interval has passed
bool EventTriggered(double interval)
{
    double currentTime = GetTime(); // Get the current time in seconds
    if (currentTime - lastUpdateTime >= interval) // Check if the interval has passed
    {
        lastUpdateTime = currentTime; // Update the last update time
        return true; // Return true if the event is triggered
    }
    return false; // Return false otherwise
}

int main()
{
    // Initialize the game window with a size of 500x620 and the title "Tetris Game"
    InitWindow(500, 620, "Tetris Game");
    SetTargetFPS(60); // Set the target frame rate to 60 FPS

    // Load a custom font for rendering text
    Font font = LoadFontEx("C:/Users/Administrator/source/repos/Tetris/Font/monogram.ttf", 64, 0, 0);

    // Create an instance of the Game class to manage game logic
    Game game = Game();

    // Main game loop: Runs until the window is closed
    while (WindowShouldClose() == false)
    {
        // Update the background music stream
        UpdateMusicStream(game.music);

        // Handle player input (e.g., moving or rotating blocks)
        game.HandleInput();

        // Move the current block down at regular intervals (every 1 second)
        if (EventTriggered(0.8))
        {
            game.MoveBlockDown();
        }

        // Begin rendering the frame
        BeginDrawing();
        ClearBackground(darkBlue); // Clear the screen with a dark blue background

        // Draw the "Score" label
        DrawTextEx(font, "Score", { 365, 15 }, 38, 2, BLACK);

        // Draw the "Next" label (for the next block preview)
        DrawTextEx(font, "Next", { 370, 175 }, 38, 2, BLACK);

        // If the game is over, display the "GAME OVER" message
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", { 320, 450 }, 38, 2, BLACK);
        }

        // Draw a rounded rectangle for the score display background
        DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, lightBlue);

        // Format the player's score as a string and calculate its size for centering
        char scoreText[10];
        sprintf_s(scoreText, sizeof(scoreText), "%d", game.score); // Convert the score to a string
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2); // Measure the size of the score text

        // Draw the player's score, centered within the score display background
        DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, BLACK);

        // Draw a rounded rectangle for the next block preview background
        DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlue);

        // Draw the game grid and blocks
        game.Draw();

        // End rendering the frame
        EndDrawing();
    }

    // Close the game window and release resources
    CloseWindow();
}
