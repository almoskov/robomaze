#include <iostream>
#include <stdlib.h>
#include <utils.h>

using namespace std;

int *bfs(int **graph, int row, int col);

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " <input_file> <row> <col>" << endl;
        return 1;
    }
    int row = atoi(argv[2]);
    int col = atoi(argv[3]);
    int **graph = readInput(argv[1], row, col);
    int *result = bfs(graph, row, col);
    return 0;
}

bool conflict_free(bool *arr, int row)
{
    for (int i = 0; i < row; i++)
        if (!arr[i])
            return false;
    return true;
}

int *bfs(int **graph, int row, int m)
{
    bool *q = new bool[row]{0};
    int *arr = new int[row];
    arr[0] = 0;
    int actual_poz = arr[0];
    int poz_cnt = 0;
    int cnt = 1;
    q[0] = true;
    while (!conflict_free(q, row))
    {
        for (int i = 0; i < row; i++)
        {
            if (graph[actual_poz][i] != 0 && !q[i])
            {
                q[i] = true;
                arr[cnt++] = i;
            }
        }
        poz_cnt++;
        actual_poz = arr[poz_cnt];
    }
    delete[] q;
    return arr;
}