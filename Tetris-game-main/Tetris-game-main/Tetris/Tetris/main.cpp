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
    double interval = 0.8 - (score / 1000.0); // Adjust the divisor to control speed scaling
    return interval > 0.2 ? interval : 0.5;  // Ensure a minimum interval of 0.5     seconds

}
// Function to draw text with a stroke (outline)
void DrawTextWithStroke(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color textColor, Color strokeColor, float strokeThickness)
{
    // Draw the stroke by rendering the text multiple times around the main text
    for (int dx = -strokeThickness; dx <= strokeThickness; dx++)
    {
        for (int dy = -strokeThickness; dy <= strokeThickness; dy++)
        {
            if (dx != 0 || dy != 0) // Skip the center position
            {
                DrawTextEx(font, text, { position.x + dx, position.y + dy }, fontSize, spacing, strokeColor);
            }
        }
    }

    // Draw the main text in the center
    DrawTextEx(font, text, position, fontSize, spacing, textColor);
}

enum GameState { MAIN_MENU, PLAYING, GAME_OVER,HOW_TO_PLAY };

int main()
{
    // Initialize the game window with a size of 500x620 and the title "Tetris Game"
    InitWindow(500, 620, "Tetris Game");
    SetTargetFPS(90); // Set the target frame rate to 90 FPS

    // Load a custom font for rendering text
    Font font = LoadFontEx("C:/Users/salon/Downloads/Tetris-game-main/Tetris-game-main/Tetris/Font/amm.ttf", 64, 0, 0);

    // Load the background image for the main menu
    Texture2D background = LoadTexture("C:/Users/salon/Downloads/Tetris-game-main/Tetris-game-main/Tetris/Image/Tetriss.png");




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
            else if (IsKeyPressed(KEY_H)) // Show "How to Play"
            {
                gameState = HOW_TO_PLAY;
            }
            else if (gameState == HOW_TO_PLAY)
            {
               

                BeginDrawing();
                ClearBackground(DARKGRAY);

                EndDrawing();
            }
        }
        else if (gameState == HOW_TO_PLAY)
        {
            if (IsKeyPressed(KEY_BACKSPACE)) // Return to the main menu
            {
                gameState = MAIN_MENU;
            }
        }
        else if (gameState == PLAYING)
        {
            if (game.gameOver)
            {
                // Allow retry when the game is over
                if (IsKeyPressed(KEY_R))
                {
                    game.Reset(); // Reset the game state
                }
            }
            else
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
            DrawTexture(background, 0, 0, WHITE);

            // Draw a rounded rectangle for the score display background
            DrawRectangleRounded({ 100, 480, 300, 60 }, 10.50, 6, WHITE);

            // Render the main menu text
            DrawTextWithStroke(font, "Press ENTER to Start", { 145, 500 }, 25,2, WHITE,BLACK,2);
            DrawTextWithStroke(font, "Press H for How to Play", { 130, 450 }, 25,2, GREEN,BLACK,2);
        }
        else if (gameState == HOW_TO_PLAY)
        {

            // Draw a rounded rectangle for the next block preview background
            DrawRectangleRounded({ 2, 10, 495, 600 }, 0, 6, DARKGRAY);

            ClearBackground(BLACK);
           
            // Render the "How to Play" screen
            DrawTextWithStroke(font, "HOW TO PLAY",{ 170, 50} , 30,2, WHITE,BLACK,2);
            DrawTextWithStroke(font, "- PRESS A/D or Left/Right to move blocks", { 20, 100 }, 24,2,WHITE,BLACK,2);
            DrawTextWithStroke(font,"- PRESS W or Up to rotate blocks", {20, 130}, 24,2, WHITE,BLACK,2);
            DrawTextWithStroke(font, "- PRESS S or Down to move blocks down", { 20, 160 }, 24,2, WHITE,BLACK,2);
            DrawTextWithStroke(font,"- Press SPACE to drop blocks", {20, 190} ,24,2, WHITE,BLACK,2);
            DrawTextWithStroke(font,"- Press TAB to pause the game", {20, 220}, 24,2, WHITE,BLACK,2);
            DrawTextWithStroke(font, "- Press UP arrow to rotate the blocks", { 20, 250 }, 24,2, WHITE,BLACK,2);
            DrawTextWithStroke(font, "- Press LEFT/RIGHT arrow to move the blocks", { 20, 280 }, 24, 2, WHITE,BLACK,2);
            DrawTextWithStroke(font, "- Press DOWN arrow to move the blocks", { 20, 310 }, 24, 2, WHITE,BLACK,2);
            DrawTextWithStroke(font, "Press BACKSPACE to return to the main menu", { 35, 430 }, 24,2, WHITE,BLACK,2);
        
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
