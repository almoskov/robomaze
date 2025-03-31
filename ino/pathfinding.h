#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "MotorControl.h"

struct Node
{
    int x, y;
    Node *parent;
};

const int mazeSize = 10;
bool visited[mazeSize][mazeSize] = {false};
Node *stack[mazeSize * mazeSize];
int stackTop = -1;

void push(Node *node)
{
    stack[++stackTop] = node;
}

Node *pop()
{
    return stackTop >= 0 ? stack[stackTop--] : nullptr;
}

void runDFS()
{
    Node *start = new Node{0, 0, nullptr};
    push(start);
    visited[0][0] = true;

    while (stackTop >= 0)
    {
        Node *current = pop();
        if (!current)
            continue;

        if (isPath())
        {
            moveForward();
            push(new Node{current->x, current->y + 1, current});
        }
        else
        {
            turnLeft();
            if (!isPath())
            {
                turnRight();
                turnRight();
            }
        }
    }
}

#endif
