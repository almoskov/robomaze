#include <iostream>
#include <stdlib.h>
#include <utils.h>

using namespace std;

void dfsback(int k, int **a, int n, bool *q, int *tomb, int &sz);
int *dfs(int **szm, int n, int m);

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
    int *result = dfs(graph, row, col);
    return 0;
}

void dfsback(int k, int **a, int n, bool *q, int *tomb, int &sz)
{

    if (sz <= n)
    {
        for (int i = 0; i < n; i++)
        {
            if (a[k][i] != 0 && !q[i])
            {
                tomb[sz] = i;
                q[i] = true;
                sz++;
                dfsback(i, a, n, q, tomb, sz);
            }
        }
    }
}

int *dfs(int **szm, int n, int m)
{
    int *lista = new int[n];
    bool *q = new bool[n]{0};
    lista[0] = 0;
    q[0] = true;
    int sz = 1;
    dfsback(0, szm, n, q, lista, sz);
    delete[] q;
    return lista;
}