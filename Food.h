#ifndef FOOD_H
#define FOOD_H
#include <raylib.h>
#include <raymath.h>
#include "LinkedList.h"

extern int cellSize;
extern int cellCount;
extern int offset;

class Food
{

public:
    Vector2 position;
    Texture2D texture;

    Food(const LinkedList<Vector2> &snakeBody);
    ~Food();
    void Draw();
    Vector2 GenerateRandomCell();
    Vector2 GenerateRandomPos(const LinkedList<Vector2>& snakeBody);
};


#endif //FOOD_H
