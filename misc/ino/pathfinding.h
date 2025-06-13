#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "control.h"
#include <queue>
#include <vector>
#include <limits.h>

struct Node {
    int x, y;
    Node* parent;
};

const int mazeSize = 10;
bool visited[mazeSize][mazeSize] = {false};
Node* stack[mazeSize * mazeSize];
int stackTop = -1;
std::queue<Node*> queue;

// Dijkstras matrix
int graph[mazeSize][mazeSize];
int dist[mazeSize][mazeSize];

// Stack for DFS
void push(Node* node) { stack[++stackTop] = node; }
Node* pop() { return stackTop >= 0 ? stack[stackTop--] : nullptr; }

// BFS queue 
void enqueue(Node* node) { queue.push(node); }
Node* dequeue() { 
    if (queue.empty()) return nullptr;
    Node* node = queue.front();
    queue.pop();
    return node;
}

void runDFS() {
    Node* start = new Node{0, 0, nullptr};
    push(start);
    visited[0][0] = true;

    while (stackTop >= 0) {
        Node* current = pop();
        if (!current) continue;

        if (isPath()) {
            moveForward();
            push(new Node{current->x, current->y + 1, current});
        } else {
            turnLeft();
            if (!isPath()) {
                turnRight();
                turnRight();
            }
        }
    }
}

void runBFS() {
    Node* start = new Node{0, 0, nullptr};
    enqueue(start);
    visited[0][0] = true;

    while (!queue.empty()) {
        Node* current = dequeue();
        if (!current) continue;

        if (isPath()) {
            moveForward();
            enqueue(new Node{current->x, current->y + 1, current});
        } else {
            turnLeft();
            if (!isPath()) {
                turnRight();
                turnRight();
            }
        }
    }
}

// Dijkstra's Algorithm (assumes predefined graph for simulation)
void runDijkstra() {
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            dist[i][j] = INT_MAX;
        }
    }

    dist[0][0] = 0;
    std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, std::greater<std::pair<int, Node*>>> pq;
    pq.push({0, new Node{0, 0, nullptr}});

    while (!pq.empty()) {
        Node* current = pq.top().second;
        pq.pop();

        if (isPath()) {
            moveForward();
        } else {
            turnLeft();
            if (!isPath()) {
                turnRight();
                turnRight();
            }
        }

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                int newX = current->x + dx;
                int newY = current->y + dy;
                if (newX >= 0 && newX < mazeSize && newY >= 0 && newY < mazeSize) {
                    int newDist = dist[current->x][current->y] + graph[newX][newY];
                    if (newDist < dist[newX][newY]) {
                        dist[newX][newY] = newDist;
                        pq.push({newDist, new Node{newX, newY, current}});
                    }
                }
            }
        }
    }
}

#endif
