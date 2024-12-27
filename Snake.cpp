//
// Created by yahia on 12/27/2024.
//
#include "Snake.h"

Snake::Snake() {
    body.insert(Vector2{6, 9});
    body.insert(Vector2{5, 9});
    body.insert(Vector2{4, 9});
}

void Snake::Draw()
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

void Snake::Update()
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

void Snake::Reset()
{
    body.clear();
    body.insert(Vector2{6, 9});
    body.insert(Vector2{5, 9});
    body.insert(Vector2{4, 9});
    direction = {1, 0};
}