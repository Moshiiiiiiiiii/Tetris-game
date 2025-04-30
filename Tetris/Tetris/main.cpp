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

// Function to calculate the interval based on the score
double CalculationInterval(int score)
{
    // Base interval is 0.8 seconds, decrease as score increases
    double interval = 0.8 - (score / 400.0); // Adjust the divisor to control speed scaling
    return interval > 0.2 ? interval : 0.4;  // Ensure a minimum interval of 0.2 seconds

}

enum GameState { MAIN_MENU, PLAYING, GAME_OVER };
int main()
{
    // Initialize the game window with a size of 500x620 and the title "Tetris Game"
    InitWindow(500, 620, "Tetris Game");
    SetTargetFPS(90); // Set the target frame rate to 90 FPS

    // Load a custom font for rendering text
    Font font = LoadFontEx("C:/Users/Administrator/Downloads/Tetris-game-main/Tetris/Font/amm.ttf", 64, 0, 0);

    // Load the background image for the main menu
    Texture2D background = LoadTexture("C:/Users/Administrator/Downloads/Tetris-game-main/Tetris/Image/Tetriss.png");

    // Create an instance of the Game class to manage game logic
    Game game = Game();

    bool isPaused = false; // Variable to track if the game is paused
    GameState gameState = MAIN_MENU; // Start in the main menu

    // Main game loop: Runs until the window is closed
    while (WindowShouldClose() == false)
    {
        // Handle input and update game state
        if (gameState == MAIN_MENU)
        {
            if (IsKeyPressed(KEY_ENTER)) // Start the game
            {
                gameState = PLAYING;
            }
        }
        else if (gameState == PLAYING)
        {
            // Toggle pause state when the 'TAB' key is pressed
            if (IsKeyPressed(KEY_TAB))
            {
                isPaused = !isPaused;

                // Pause or resume the music based on the pause state
                if (isPaused)
                {
                    PauseMusicStream(game.music); // Pause the music
                }
                else
                {
                    ResumeMusicStream(game.music); // Resume the music
                }
            }

            // Update the background music stream
            UpdateMusicStream(game.music);

            if (!isPaused) // Only update game logic if the game is not paused
            {
                // Handle player input (e.g., moving or rotating blocks)
                game.HandleInput();

                // Calculate the interval based on the current score
                double interval = CalculationInterval(game.score);

                // Move the current block down at regular intervals (every 1 second)
                if (EventTriggered(interval))
                {
                    game.MoveBlockDown();
                }
            }
        }

        // Begin rendering the frame
        BeginDrawing();
        ClearBackground(DARKGRAY); // Clear the screen with a dark blue background

        if (gameState == MAIN_MENU)
        {
            // Draw the background image
            DrawTexture(background,0, 0, WHITE);

            // Draw a rounded rectangle for the score display background
            DrawRectangleRounded({ 100, 480, 300, 60 }, 10.50, 6, WHITE);

            // Render the main menu text
            DrawText("Press ENTER to Start", 110, 500, 25, BLACK);

           
        
        }
        else if (gameState == PLAYING)
        {
            // Render the game
            // Draw the "Score" label
            DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE);

            // Draw the "Next" label (for the next block preview)
            DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE);

            // If the game is over, display the "GAME OVER" message
            if (game.gameOver)
            {
                DrawTextEx(font, "GAME OVER", { 320, 450 }, 38, 2, WHITE);
            }
            // If the game is paused, display the "PAUSED" message
            if (isPaused)
            {
                DrawTextEx(font, "PAUSED", { 360, 500 }, 38, 2, WHITE);
            }

            // Draw a rounded rectangle for the score display background
            DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, lightBlue);

            // Format the player's score as a string and calculate its size for centering
            char scoreText[10];
            sprintf_s(scoreText, sizeof(scoreText), "%d", game.score); // Convert the score to a string
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2); // Measure the size of the score text

            // Draw the player's score, centered within the score display background
            DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);

            // Draw a rounded rectangle for the next block preview background
            DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlue);

            // Draw the game grid and blocks
            game.Draw();
        }

        EndDrawing();
    }

    // Unload the background texture
    UnloadTexture(background);

    // Close the game window and release resources
    CloseWindow();
}
