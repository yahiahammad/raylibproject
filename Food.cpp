#include "Food.h"

Food::Food(const LinkedList<Vector2> &snakeBody)
{
    Image image = LoadImage("Graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = GenerateRandomPos(snakeBody);
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::Draw()
{
    DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
}

Vector2 Food::GenerateRandomCell()
{
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);
    return Vector2{x, y};
}

Vector2 Food::GenerateRandomPos(const LinkedList<Vector2>& snakeBody)
{
    Vector2 position = GenerateRandomCell();
    while (snakeBody.Search(position))
    {
        position = GenerateRandomCell();
    }
    return position;
}