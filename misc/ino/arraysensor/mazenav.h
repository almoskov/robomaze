#ifndef MAZE_NAVIGATION_H
#define MAZE_NAVIGATION_H

#include <Arduino.h>
#include <vector>
#include <queue>
#include <stack>

// === Direction & Movement Enums === //
enum Direction
{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

enum Movement
{
    MOVE_FORWARD,
    TURN_LEFT,
    TURN_RIGHT,
    TURN_AROUND
};

// === Node Struct for Maze Grid === //
struct Node
{
    int x, y;
    Node(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Node &other) const
    {
        return x == other.x && y == other.y;
    }
};

// === Planner for Known Mazes === //
class MazePlanner
{
public:
    MazePlanner(const std::vector<std::vector<int>> &maze)
        : maze_(maze), rows(maze.size()), cols(maze[0].size()) {}

    std::vector<Node> findShortestPath()
    {
        Node start, goal;
        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                if (maze_[y][x] == 2)
                    start = Node(x, y);
                if (maze_[y][x] == 3)
                    goal = Node(x, y);
            }
        }

        std::queue<Node> q;
        std::vector<std::vector<Node>> parent(rows, std::vector<Node>(cols, {-1, -1}));
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
        std::vector<std::vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        q.push(start);
        visited[start.y][start.x] = true;

        while (!q.empty())
        {
            Node curr = q.front();
            q.pop();
            if (curr == goal)
                break;

            for (auto d : dir)
            {
                int nx = curr.x + d[0], ny = curr.y + d[1];
                if (nx >= 0 && ny >= 0 && nx < cols && ny < rows &&
                    maze_[ny][nx] != 0 && !visited[ny][nx])
                {
                    q.push({nx, ny});
                    visited[ny][nx] = true;
                    parent[ny][nx] = curr;
                }
            }
        }

        std::vector<Node> path;
        for (Node at = goal; at.x != -1; at = parent[at.y][at.x])
        {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    std::vector<std::vector<int>> maze_;
    int rows, cols;
};

// === Explorer for Unknown Maze (DFS) === //
class MazeExplorer
{
public:
    MazeExplorer() {}

    void exploreMazeDFS()
    {
        std::stack<Node> stack;
        Node current(0, 0); // Starting at origin
        stack.push(current);
        visited.push_back(current);

        while (!stack.empty())
        {
            current = stack.top();

            if (hasUnvisitedNeighbor(current))
            {
                Node next = getUnvisitedNeighbor(current);
                moveTo(current, next);
                stack.push(next);
                visited.push_back(next);
            }
            else
            {
                stack.pop();
                if (!stack.empty())
                {
                    moveTo(current, stack.top()); // Backtrack
                }
            }
        }
    }

    // === Movement Primitives === //
    void moveForward(); // Follows line until junction
    void turnLeft();    // Turns robot 90° left
    void turnRight();   // Turns robot 90° right
    void turnAround();  // Turns robot 180°
    void stopMotors();  // Stops all motors
    bool isJunction();  // Returns true at junction

private:
    std::vector<Node> visited;

    bool hasUnvisitedNeighbor(const Node &node)
    {
        for (auto dir : {NORTH, EAST, SOUTH, WEST})
        {
            Node n = neighbor(node, dir);
            if (!isVisited(n) && isPath(n))
                return true;
        }
        return false;
    }

    Node getUnvisitedNeighbor(const Node &node)
    {
        for (auto dir : {NORTH, EAST, SOUTH, WEST})
        {
            Node n = neighbor(node, dir);
            if (!isVisited(n) && isPath(n))
                return n;
        }
        return node;
    }

    bool isVisited(const Node &node)
    {
        for (const auto &n : visited)
        {
            if (n == node)
                return true;
        }
        return false;
    }

    Node neighbor(const Node &node, Direction dir)
    {
        switch (dir)
        {
        case NORTH:
            return Node(node.x, node.y - 1);
        case EAST:
            return Node(node.x + 1, node.y);
        case SOUTH:
            return Node(node.x, node.y + 1);
        case WEST:
            return Node(node.x - 1, node.y);
        }
        return node;
    }

    bool isPath(const Node &node)
    {
        // Placeholder TODO: this needs be determined with sensors
        return true;
    }

    void moveTo(const Node &from, const Node &to)
    {
        int dx = to.x - from.x;
        int dy = to.y - from.y;

        Direction desired;
        if (dx == 1)
            desired = EAST;
        else if (dx == -1)
            desired = WEST;
        else if (dy == 1)
            desired = SOUTH;
        else
            desired = NORTH;

        int turn = (desired - currentDirection + 4) % 4;
        switch (turn)
        {
        case 0:
            break;
        case 1:
            turnRight();
            break;
        case 2:
            turnAround();
            break;
        case 3:
            turnLeft();
            break;
        }

        moveForward();
        currentDirection = desired;
    }

    Direction currentDirection = NORTH;
};

#endif // MAZE_NAVIGATION_H
