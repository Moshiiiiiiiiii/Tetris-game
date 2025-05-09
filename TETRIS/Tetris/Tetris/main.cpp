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
    return interval > 0.2 ? interval : 0.5;  // Ensure a minimum interval of 0.5 seconds
}
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

enum GameState { MAIN_MENU, PLAYING, GAME_OVER, HOW_TO_PLAY, PAUSE };

int main()
{

    // Initialize the game window with a size of 500x620 and the title "Tetris Game"
    InitWindow(500, 620, "Tetris Game");
    SetTargetFPS(90); // Set the target frame rate to 90 FPS

    // Load a custom font for rendering text
    Font font = LoadFontEx("C::/Users/SNY IT Solutions/Downloads/Tetris-game-main/Tetris-game-main/Tetris-game-main/Tetris/Font/amm.ttf", 64, 0, 0);

    // Load the background image for the main menu
    Texture2D background = LoadTexture("C:/Users/SNY IT Solutions/Downloads/Tetris-game-main/Tetris-game-main/Tetris-game-main/Tetris/Tetriss.png");
    Texture2D background2 = LoadTexture("C:/Users/SNY IT Solutions/Downloads/Tetris-game-main/Tetris-game-main/Tetris-game-main/Tetris/sky.jpg");
    Texture2D background3 = LoadTexture("C:/Users/SNY IT Solutions/Downloads/Tetris-game-main/Tetris-game-main/Tetris-game-main/Tetris/starry.jpg");
    Game game = Game();
    // Create an instance of the Game class to manage game logic
  

    bool isPaused = false; // Variable to track if the game is paused
    GameState gameState = MAIN_MENU; // Start in the main menu

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
                gameState = GAME_OVER; // Transition to the GAME_OVER state
            }
            else
            {
                if (IsKeyPressed(KEY_TAB)) // Pause the game
                {
                    gameState = PAUSE;
                    isPaused = true;
                }

                UpdateMusicStream(game.music);

                if (!isPaused)
                {
                    game.HandleInput();
                    double interval = CalculationInterval(game.score);
                    if (EventTriggered(interval))
                    {
                        game.MoveBlockDown();
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
        }

        // Begin rendering the frame
        BeginDrawing();
        ClearBackground(WHITE);

        // Render based on the current game state
        if (gameState == MAIN_MENU)
        {
            // Draw the main menu
            DrawTexture(background, 0, 0, WHITE);
            DrawRectangleRoundedWithStroke({ 100, 480, 300, 60 }, 0.3f, 6, GRAY, BLACK, 3.0f);
            DrawTextWithStroke(font, "Press \"ENTER\" to Start", { 135, 500 }, 25, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"H\" for How to Play", { 120, 450 }, 25, 2, GREEN, BLACK, 2);
            DrawTextWithStroke(font, "Press \"ESCAPE\" to Quit", { 133, 550 }, 25, 2, RED, BLACK, 2);
        }
        else if (gameState == HOW_TO_PLAY)
        {
            // Draw the "How to Play" screen
            DrawRectangleRounded({ 2, 10, 495, 600 }, 0, 6, DARKGRAY);
            DrawTextureEx(background3, { 0, -300 }, 0.0f, 0.9f, WHITE);
            DrawTextWithStroke(font, "HOW TO PLAY", { 145, 50 }, 50, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- PRESS \"A/D\" or Left/Right to move blocks", { 20, 130 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- PRESS \"W or Up\" to rotate blocks", { 20, 160 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- PRESS \"S or Down\" to move blocks down", { 20, 190 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- Press \"SPACE\" to drop blocks", { 20, 220 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- Press \"TAB\" to pause the game", { 20, 250 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"BACKSPACE\" to return to the main menu", { 25, 570 }, 24, 2, WHITE, BLACK, 2);
        }
        else if (gameState == PLAYING)
        {
            // Draw the game
            DrawTextureEx(background2, { 0, 0 }, 0.0f, 0.7f, WHITE);
            DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE);
            DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE);
            DrawRectangleRoundedWithStroke({ 320, 50, 170, 60 }, 0.3f, 6, GRAY, BLACK, 3.0f);
            char scoreText[10];
            sprintf_s(scoreText, sizeof(scoreText), "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
            DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);
            DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlue);
            game.Draw();
        }
        else if (gameState == GAME_OVER)
        {
            // Draw the "Game Over" screen
            ClearBackground(RED);
            DrawTextWithStroke(font, "GAME OVER", { 100, 100 }, 80, 2, WHITE, BLACK, 3);
            char scoreText[20];
            sprintf_s(scoreText, sizeof(scoreText), "Score: %d", game.score);
            DrawTextWithStroke(font, scoreText, { 40, 300 }, 40, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"R\" to Retry", { 40, 400 }, 30, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"M\" Back to Main Menu", { 40, 450 }, 30, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"ESCAPE\" to Quit", { 133, 550 }, 25, 2, WHITE, BLACK, 2);
        }
        else if (gameState == PAUSE)
        {
            // Check if the 'B' key is pressed to resume the game
            if (IsKeyPressed(KEY_B))
            {
                gameState = PLAYING;
                isPaused = false; // Ensure the paused state is cleared
            }

            BeginDrawing();
            // Draw the background image with a zoom-out effect (scale < 1.0)
            DrawTextureEx(background2, { 0, 0 }, 0.0f, 0.7f, WHITE); // Scale down to 70% of the original size
            // Render the "PAUSED" message
            DrawTextWithStroke(font, "PAUSED", { 155, 100 }, 80, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"B\" to Continue", { 135, 300 }, 30, 2, WHITE, BLACK, 2);
            EndDrawing();

            // Skip the rest of the loop to avoid rendering other states
            continue;
        }

        // Begin rendering the frame
        BeginDrawing();
        ClearBackground(WHITE); // Clear the screen with a dark blue background

        if (gameState == MAIN_MENU)
        {
            // Draw the background image
            DrawTexture(background, 0, 0, WHITE);

            // Example: Draw a rounded rectangle with a white fill and a black stroke
            DrawRectangleRoundedWithStroke(
                { 100, 480, 300, 60 }, // Rectangle position and size
                0.3f,                  // Roundness
                6,                     // Segments
                GRAY,                 // Fill color
                BLACK,                 // Stroke color
                3.0f                   // Stroke thickness
            );

            // Render the main menu text
            DrawTextWithStroke(font, "Press \"ENTER\" to Start", { 135, 500 }, 25, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"H\" for How to Play", { 120, 450 }, 25, 2, GREEN, BLACK, 2);
            DrawTextWithStroke(font, "Press \"ESCAPE\" to Quit", { 133, 550 }, 25, 2, RED, BLACK, 2);
        }
        else if (gameState == HOW_TO_PLAY)
        {
            // Draw a rounded rectangle for the next block preview background
            DrawRectangleRounded({ 2, 10, 495, 600 }, 0, 6, DARKGRAY);


            // Draw the background image with a zoom-out effect (scale < 1.0)
            DrawTextureEx(background3, { 0, -300 }, 0.0f, 0.9f, WHITE); // Scale down to 70% of the original size

            // Render the "How to Play" screen
            DrawTextWithStroke(font, "HOW TO PLAY", { 145, 50 }, 50, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- PRESS \"A/D\" or Left/Right to move blocks", { 20, 130 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- PRESS \"W or Up\" to rotate blocks", { 20, 160 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- PRESS \"S or Down\" to move blocks down", { 20, 190 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- Press \"SPACE\" to drop blocks", { 20, 220 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "- Press \"TAB\" to pause the game", { 20, 250 }, 24, 2, WHITE, BLACK, 2);
            DrawTextWithStroke(font, "Press \"BACKSPACE\" to return to the main menu", { 25, 570 }, 24, 2, WHITE, BLACK, 2);
        }
        else if (gameState == PLAYING)
        {

            // Draw the background image with a zoom-out effect (scale < 1.0)
            DrawTextureEx(background2, { 0, 0 }, 0.0f, 0.7f, WHITE); // Scale down to 70% of the original size

            // Render the game
            // Draw the "Score" label
            DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE);

            // Draw the "Next" label (for the next block preview)
            DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE);

            // Draw the "next rectangle" background
            DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlue);

            // Draw the game grid and blocks
            game.Draw();

            DrawRectangleRoundedWithStroke(
                { 320, 50, 170, 60 }, // Rectangle position and size
                0.3f,                  // Roundness
                6,                     // Segments
                GRAY,                 // Fill color
                BLACK,                 // Stroke color
                3.0f                   // Stroke thickness
            );


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
        {
            EndDrawing();
        }

        // Unload all the background texture
        UnloadTexture(background);
        UnloadTexture(background2);
        UnloadTexture(background3);

        // Close the game window and release resources
        CloseWindow();
    }

}