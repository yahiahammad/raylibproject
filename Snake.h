#ifndef SNAKE_H
#define SNAKE_H
#include <raylib.h>
#include <raymath.h>
#include "LinkedList.h"

extern int cellSize;
extern int cellCount;
extern int offset;
extern Color darkGreen;


class Snake
{
public:
    LinkedList<Vector2> body ;//= {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;

    Snake();
    void Draw();
    void Update();
    void Reset();
};



#endif //SNAKE_H
