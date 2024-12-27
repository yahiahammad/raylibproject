#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include <raymath.h>
#include "LinkedList.h"
#include "Snake.h"
#include "Food.h"


class Game
{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;
    Sound eatSound;
    Sound wallSound;

    Game();
    ~Game();
    void Draw();
    void Update();
    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void GameOver();
    void CheckCollisionWithTail();
};



#endif //GAME_H
