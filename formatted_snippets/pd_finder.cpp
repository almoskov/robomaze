/*
 *   Navigation logic for a pathfinder that uses a predetermined path.
 *
 *   hardcoded elements :
 *   MAX_PATH - maximum number of moves in the path
 *   ROWS - number of rows in the grid
 *   COLS - number of columns in the grid
 *   grid - the grid itself, where:
 *       0 - wall
 *       1 - navigable space
 *       2 - start point
 *       3 - end point
 */
const int FORWARD = 1;
const int RIGHT = 2;
const int LEFT = 3;
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
    // hardcoded "grid"
    // int grid[ROWS][COLS] ;
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
            return FORWARD;
        if (diff == 1)
            return LEFT;
        if (diff == 3)
            return RIGHT;
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
