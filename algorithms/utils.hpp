#include <utils.h>
#include <iostream>
#include <fstream>

using namespace std;

int **beolvas(const char *file, int &row, int &col)
{
    ifstream f(file);
    f >> row >> col;
    int **szm = new int *[row];
    for (int i = 0; i < row; i++)
    {
        szm[i] = new int[row]{0};
    }
    for (int i = 0; i < col; i++)
    {
        int x, y;
        f >> x >> y;
        szm[x][y] = 1;
        szm[y][x] = szm[x][y];
    }
    f.close();
    return szm;
}