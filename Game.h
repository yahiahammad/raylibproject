#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include <raymath.h>
#include "LinkedList.h"
#include "Snake.h"
#include "Food.h"

enum Status {
    RUNNING = 0,
    PAUSED,
    GAMEOVER
};
class Game
{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    Status status = RUNNING;
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
