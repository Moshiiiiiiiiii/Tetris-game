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
    return interval > 0.2 ? interval : 0.32;  // Ensure a minimum interval of 0.5 seconds
}

// Draws a rounded rectangle with a stroke
void DrawRectangleRoundedWithStroke(Rectangle rect, float roundness, int segments, Color fillColor, Color strokeColor, float strokeThickness)
{
    // Draw the stroke (outer rectangle)
    DrawRectangleRounded(rect, roundness, segments, strokeColor);

    // Adjust the rectangle size for the inner fill
    Rectangle innerRect = {
        rect.x + strokeThickness,
        rect.y + strokeThickness,
        rect.width - 2 * strokeThickness,
        rect.height - 2 * strokeThickness
    };

    // Draw the inner rectangle (fill)
    DrawRectangleRounded(innerRect, roundness, segments, fillColor);
}

// Draws text with a stroke
void DrawTextWithStroke(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color textColor, Color strokeColor, float strokeThickness)
{
    // Draw the stroke by rendering the text multiple times around the main text
    for (int dy = -static_cast<int>(strokeThickness); dy <= static_cast<int>(strokeThickness); dy++)
    {
        for (int dx = -static_cast<int>(strokeThickness); dx <= static_cast<int>(strokeThickness); dx++)
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

// Enum to represent the different game states
enum GameState { MAIN_MENU, PLAYING, GAME_OVER, HOW_TO_PLAY, PAUSE };

int main()
{
    // Initialize the game window
    InitWindow(500, 620, "Tetris Game");
    SetTargetFPS(90); // Set the target frames per second

    // Load resources (textures and fonts) once before the game loop
    Font font = LoadFontEx("C:/Users/salon/Downloads/Tetris-game-main (1)/Tetris-game-main/TETRIS/Tetris/Font/amm.ttf", 64, 0, 0);
    Texture2D BG1 = LoadTexture("C:/Users/salon/Downloads/Tetris-game-main (1)/Tetriss.png");
    Texture2D BG2 = LoadTexture("C:/Users/salon/Downloads/Tetris-game-main (1)/sky.jpg");
    Texture2D BG3 = LoadTexture("C:/Users/salon/Downloads/Tetris-game-main (1)/pic1.jpg");

    // Initialize the game object and variables
    Game game = Game();
    bool isPaused = false; // Tracks whether the game is paused
    GameState gameState = MAIN_MENU; // Start in the main menu

    // Main game loop
    while (!WindowShouldClose()) // Loop until the window is closed
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
            if (game.gameOver) // Check if the game is over
            {
                gameState = GAME_OVER; // Transition to the GAME_OVER state
            }
            else
            {
                if (IsKeyPressed(KEY_TAB)) // Pause the game
                {
                    gameState = PAUSE;
                    isPaused = true;
                }

                UpdateMusicStream(game.music); // Update the background music stream

                if (!isPaused) // If the game is not paused
                {
                    game.HandleInput(); // Handle player input
                    double interval = CalculationInterval(game.score); // Calculate the interval based on the score
                    if (EventTriggered(interval)) // Check if the interval has passed
                    {
                        game.MoveBlockDown(); // Move the current block down
                    }
                }
            }
        }
        else if (gameState == PAUSE)
        {
            if (IsKeyPressed(KEY_B)) // Resume the game
            {
                gameState = PLAYING;
                isPaused = false;
            }
            else if (IsKeyPressed(KEY_R)) // Retry the game
            {
                game.Reset();
                gameState = PLAYING;
                isPaused = false;
            }
            else if (IsKeyPressed(KEY_M)) // Return to the main menu
            {
                game.Reset();
                gameState = MAIN_MENU;
                isPaused = false;
            }
        }
        else if (gameState == GAME_OVER)
        {
            if (IsKeyPressed(KEY_R)) // Retry the game
            {
                game.Reset();
                gameState = PLAYING;
            }
            else if (IsKeyPressed(KEY_M)) // Return to the main menu
            {
                game.Reset();
                gameState = MAIN_MENU;
            }
        }

        // Begin rendering the frame
        BeginDrawing();
        ClearBackground(DARKGRAY); // Clear the screen with a dark gray background

        // Render based on the current game state
        if (gameState == MAIN_MENU)
        {
            DrawTexture(BG1, 0, 0, WHITE); // Draw the main menu background
            DrawRectangleRoundedWithStroke({ 100, 480, 300, 60 }, 0.3f, 6, GRAY, BLACK, 3.0f); // Draw a button
            DrawTextWithStroke(font, "Press \"ENTER\" to Play", { 135, 500 }, 25, 2, WHITE, BLACK, 2); // Draw text
            DrawTextWithStroke(font, "Press \"H\" for How to play ", { 120, 450 }, 25, 2, GREEN, BLACK, 2);
            DrawTextWithStroke(font, "Press \"ESCAPE\" to Quit", { 133, 550 }, 25, 2, RED, BLACK, 2);
        }
        else if (gameState == PAUSE)
        {
            DrawTextureEx(BG2, { 0, 0 }, 0.0f, 0.7f, WHITE); // Draw the pause screen background
            DrawTextWithStroke(font, "PAUSED", { 155, 100 }, 80, 5, WHITE, BLACK, 5); // Draw "PAUSED" text
            DrawTextWithStroke(font, "Press \"B\" to Back", { 165, 500 }, 25, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"M\" Back to Main Menu", { 80, 450 }, 30, 2, WHITE, BLACK, 2);
        }
        else if (gameState == HOW_TO_PLAY)
        {
            DrawRectangleRounded({ 2, 10, 495, 600 }, 0, 6, DARKGRAY); // Draw a background for the "How to Play" screen
            DrawTextureEx(BG3, { 0, -300 }, 0.0f, 0.9f, WHITE); // Draw an image
            DrawTextWithStroke(font, "HOW TO PLAY", { 145, 50 }, 50, 2, WHITE, BLACK, 2); // Draw the title
            DrawTextWithStroke(font, "- PRESS \"A/D\" or Left/Right to move blocks", { 20, 130 }, 24, 2, WHITE, BLACK, 2); // Instructions
            DrawTextWithStroke(font, "- PRESS \"W or Up\" to rotate blocks", { 20, 160 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- PRESS \"S or Down\" to move blocks down", { 20, 190 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- Press \"SPACE\" to drop blocks", { 20, 220 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- Press \"TAB\" to pause the game", { 20, 250 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"BACKSPACE\" to return to the main menu", { 25, 570 }, 24, 2, WHITE, BLACK, 2);
        }
        else if (gameState == PLAYING)
        {
            DrawTextureEx(BG2, { 0, 0 }, 0.0f, 0.7f, WHITE); // Draw the game background
            DrawTextWithStroke(font, "SCORE", { 365, 15 }, 30, 2, WHITE, BLACK, 2); // Draw the score label
            DrawRectangleRoundedWithStroke({ 320, 140, 170, 180 }, 0.3f, 6, GRAY, BLACK, 3.0f); // Draw the "next block" area
            DrawTextWithStroke(font, "NEXT", { 380, 160 }, 30, 2, WHITE, BLACK, 2); // Draw the "NEXT" label
            DrawRectangleRoundedWithStroke({ 320, 50, 170, 60 }, 0.3f, 6, GRAY, BLACK, 3.0f); // Draw the score area

            // Draw the score
            char scoreText[10];
            sprintf_s(scoreText, sizeof(scoreText), "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
            DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);

            game.Draw(); // Draw the game grid and blocks
        }
        else if (gameState == GAME_OVER)
        {
            ClearBackground(RED); // Set the background to red
            DrawTextWithStroke(font, "GAME OVER", { 100, 100 }, 80, 2, WHITE, BLACK, 3); // Draw "GAME OVER"
            char scoreText[20];
            sprintf_s(scoreText, sizeof(scoreText), "Score: %d", game.score); // Display the final score
            DrawTextWithStroke(font, scoreText, { 40, 300 }, 40, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"R\" to Retry", { 40, 400 }, 30, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"M\" Back to Main Menu", { 40, 450 }, 30, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"ESCAPE\" to Quit", { 133, 550 }, 25, 2, WHITE, BLACK, 2);
        }

        EndDrawing(); // End rendering the frame
    }

    // Unload resources after the game loop ends
    UnloadTexture(BG1);
    UnloadTexture(BG2); 
    UnloadTexture(BG3);
    UnloadFont(font);

    // Close the game window
    CloseWindow();

    return 0;
}
