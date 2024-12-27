#include "Game.h"

Game::Game()
{
    InitAudioDevice();
    eatSound = LoadSound("Sounds/eat.mp3");
    wallSound = LoadSound("Sounds/wall.mp3");
}

Game::~Game()
{
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    CloseAudioDevice();
}

void Game::Draw()
{
    food.Draw();
    snake.Draw();
}

void Game::Update()
{
    if (running)
    {
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }
}

void Game::CheckCollisionWithFood()
{
    if (Vector2Equals(snake.body.getHead()->data, food.position))
    {
        food.position = food.GenerateRandomPos(snake.body);
        snake.addSegment = true;
        score++;
        PlaySound(eatSound);
    }
}

void Game::CheckCollisionWithEdges()
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

void Game::GameOver()
{
    snake.Reset();
    food.position = food.GenerateRandomPos(snake.body);
    running = false;
    score = 0;
    PlaySound(wallSound);
}

void Game::CheckCollisionWithTail()
{
    LinkedList<Vector2> headlessBody = snake.body;
    headlessBody.erase(0);
    if (headlessBody.Search(snake.body.getHead()->data) == true)
    {
        GameOver();
    }
}