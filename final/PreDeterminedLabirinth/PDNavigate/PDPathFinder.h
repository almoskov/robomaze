#ifndef PDPATHFINDER_H
#define PDPATHFINDER_H

#define ROWS 10
#define COLS 10

/* this is for the "easy grid" example
#define ROWS 4
#define COLS 3
*/

/* this is for the "medium grid" example
#define ROWS 8
#define COLS 5
*/

#define MAX_PATH 100
// #include <stdio.h>
// #include <iostream>
//  using namespace std;

const int PF_FORWARD = 1;
const int PF_RIGHT = 2;
const int PF_LEFT = 3;

class PathFinderPredetermined
{
public:
    short moves[MAX_PATH];
    int moveCount = 0;

    short *solve()
    {
        pathLength = 0;
        moveCount = 0;

        int start = findStartOrEnd(2);
        int sx = start / COLS;
        int sy = start % COLS;

        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                visited[i][j] = false;

        dfs(sx, sy, startDir);
        computeMoves();

        return moves;
    }

private:
    struct Node
    {
        int x, y, dir, cost;
    };
    // hardcoded "hard grid"
    int grid[ROWS][COLS] = {
        {2, 1, 1, 1, 0, 0, 1, 1, 1, 0},
        {1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 0, 1, 0, 1},
        {0, 1, 0, 0, 0, 1, 0, 1, 1, 1},
        {0, 1, 1, 0, 1, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 0, 3, 1, 1, 1, 0, 1}};
    /* this is the "medium grid"
    int grid[ROWS][COLS] = {
        {2, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 0, 3}};
    */
    /* this is the "easy grid"
    int grid[ROWS][COLS] = {
        {2, 0, 3},
        {1, 1, 1},
        {1, 0, 0},
        {1, 0, 0}};
    */
    Node path[MAX_PATH];
    int pathLength = 0;

    int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // S,E,N,W
    int startDir = 0;                                          // facing south

    bool visited[ROWS][COLS];

    bool isValid(int x, int y)
    {
        return x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] != 0;
    }

    bool isIntersection(int x, int y)
    {
        int count = 0;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            if (isValid(nx, ny))
                count++;
        }
        return count > 2;
    }

    int findStartOrEnd(int val)
    {
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                if (grid[i][j] == val)
                    return i * COLS + j;
        return -1;
    }

    bool dfs(int x, int y, int fromDir)
    {
        if (grid[x][y] == 3)
        {
            path[pathLength++] = {x, y, fromDir, 0};
            return true;
        }

        visited[x][y] = true;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            if (isValid(nx, ny) && !visited[nx][ny])
            {
                if (dfs(nx, ny, i))
                {
                    path[pathLength++] = {x, y, fromDir, 0};
                    return true;
                }
            }
        }
        return false;
    }

    int getTurn(int prevDir, int currDir)
    {
        int diff = (currDir - prevDir + 4) % 4;
        if (diff == 0)
            return PF_FORWARD;
        if (diff == 1)
            return PF_LEFT;
        if (diff == 3)
            return PF_RIGHT;
        return -1;
    }

    void computeMoves()
    {
        int prevDir = startDir;
        for (int i = pathLength - 1; i > 0; i--)
        {
            int x = path[i].x;
            int y = path[i].y;
            int currDir = path[i - 1].dir;

            if (isIntersection(x, y) || currDir != prevDir)
            {
                moves[moveCount++] = getTurn(prevDir, currDir);
                prevDir = currDir;
            }
        }
    }
};

/*int main() // this code snippet is only for debbuging purposes
{
    PathFinderPredetermined pathFinder;
    pathFinder.solve();
    return 0;
}*/

#endif // PATHFINDER_H
