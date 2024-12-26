#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "LinkedList.h"
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

class Snake
{
public:
    LinkedList<Vector2> body ;//= {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;
    Snake() {
        body.insert(Vector2{6, 9});
        body.insert(Vector2{5, 9});
        body.insert(Vector2{4, 9});
    }

    void Draw()
    {
        if (body.getHead() != nullptr)
        {
            float headX = body.getHead()->data.x;
            float headY = body.getHead()->data.y;
            Rectangle headRect = Rectangle{offset + headX * cellSize, offset + headY * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(headRect, 0.9, 6, RED); // Use a distinct color for the head (e.g., RED)
        }

        // Draw the rest of the body with the usual color
        LinkedList<Vector2>::NodePointer ptr = body.getHead();
        if (ptr != nullptr)
            ptr = ptr->next; // Skip the head node

        while (ptr != nullptr)
        {
            float x = ptr->data.x;
            float y = ptr->data.y;
            Rectangle segment = Rectangle{offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen); // Use the normal body color
            ptr = ptr->next;
        }


    }

    void Update()
    {
        body.insertInFront(Vector2Add(body.getHead()->data, direction));
        if (addSegment == true)
        {
            addSegment = false;
        }
        else
        {

            body.eraseLast();
        }
    }

    void Reset()
    {
        body.clear();
        body.insert(Vector2{6, 9});
        body.insert(Vector2{5, 9});
        body.insert(Vector2{4, 9});
        direction = {1, 0};
    }
};

class Food
{

public:
    Vector2 position;
    Texture2D texture;

    Food(const LinkedList<Vector2> &snakeBody)
    {
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

    Vector2 GenerateRandomPos(const LinkedList<Vector2>& snakeBody)
    {
        Vector2 position = GenerateRandomCell();
        while (snakeBody.Search(position))
        {
            position = GenerateRandomCell();
        }
        return position;
    }
};

class Game
{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;
    Sound eatSound;
    Sound wallSound;

    Game()
    {
        InitAudioDevice();
        eatSound = LoadSound("Sounds/eat.mp3");
        wallSound = LoadSound("Sounds/wall.mp3");
    }

    ~Game()
    {
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        if (running)
        {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }

    void CheckCollisionWithFood()
    {
        if (Vector2Equals(snake.body.getHead()->data, food.position))
        {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
            score++;
            PlaySound(eatSound);
        }
    }

    void CheckCollisionWithEdges()
    {
        if (snake.body.getHead()->data.x == cellCount || snake.body.getHead()->data.x == -1)
        {
            GameOver();
        }
        if (snake.body.getHead()->data.y == cellCount || snake.body.getHead()->data.y == -1)
        {
            GameOver();
        }
    }

    void GameOver()
    {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
        score = 0;
        PlaySound(wallSound);
    }

    void CheckCollisionWithTail()
    {
        LinkedList<Vector2> headlessBody = snake.body;
        headlessBody.erase(0);
        if (headlessBody.Search(snake.body.getHead()->data) == true)
        {
            GameOver();
        }
    }
};

int main()
{
    cout << "Starting the game..." << endl;
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Retro Snake");
    SetTargetFPS(60);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        if (EventTriggered(0.2))
        {
            allowMove = true;
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1 && allowMove)
        {
            game.snake.direction = {0, -1};
            game.running = true;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1 && allowMove)
        {
            game.snake.direction = {0, 1};
            game.running = true;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1 && allowMove)
        {
            game.snake.direction = {-1, 0};
            game.running = true;
            allowMove = false;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1 && allowMove)
        {
            game.snake.direction = {1, 0};
            game.running = true;
            allowMove = false;
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