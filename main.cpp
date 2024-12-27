#include <iostream>
#include <raylib.h>
#include "Game.h"
using namespace std;

static bool allowMove = false;
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
int offset = 75;

double lastUpdateTime = 0;


bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    cout << "Starting the game..." << endl;
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Snake Game");
    Image icon = LoadImage("Graphics/icon.png");
    SetWindowIcon( icon );
    UnloadImage(icon);
    SetTargetFPS(144);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        if (EventTriggered(0.15) && game.status == RUNNING)
        {
            allowMove = true;
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1 && allowMove)
        {
            game.snake.direction = {0, -1};
            game.status = RUNNING;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1 && allowMove)
        {
            game.snake.direction = {0, 1};
            game.status = RUNNING;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1 && allowMove)
        {
            game.snake.direction = {-1, 0};
            game.status = RUNNING;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1 && allowMove)
        {
            game.snake.direction = {1, 0};
            game.status = RUNNING;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_SPACE) && game.status == RUNNING) {
            allowMove = false;
            game.status = PAUSED;
        }
        else if (IsKeyPressed(KEY_SPACE) && game.status == PAUSED) {
            allowMove = true;
            game.status = RUNNING;
        }
        if (IsKeyPressed(KEY_SPACE) && game.status == GAMEOVER) {
            allowMove = true;
            game.status = RUNNING;
        }
        else if (game.status == GAMEOVER) {
            allowMove = false;
            game.status = GAMEOVER;
        }


        // Drawing
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10}, 5, darkGreen);
        DrawText("Snake Game - Linked List", offset - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);
        game.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}