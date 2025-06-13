// Grafalgoritmusok hazi feladat : Dijkstra algoritmus

#include <iostream>
#include <fstream>
#define INF 1000000000
using namespace std;

int **beolvas(const char *, int &, int &);
void dijkstra(int **, int, int);

int main()
{
    int n, m;
    int **szm = beolvas("graf.txt", n, m);
    dijkstra(szm, n, 1);
    for (int i = 0; i < n; i++)
    {
        delete[] szm[i];
    }
    delete[] szm;
    return 0;
}

int **beolvas(const char *file, int &n, int &m)
{
    ifstream f(file);
    f >> n >> m;
    int **szm = new int *[n];
    for (int i = 0; i < n; i++)
    {
        szm[i] = new int[n]{0};
    }
    for (int i = 0; i < m; i++)
    {
        int x, y, v;
        f >> x >> y >> v;
        szm[x][y] = v;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!szm[i][j])
            {
                szm[i][j] = INF;
            }
            // cout << szm[i][j] << " ";
        } // cout << endl;
    }
    f.close();
    return szm;
}

void dijkstra(int **szm, int n, int kp)
{
    int *dist = new int[n]{0};
    int *ut = new int[n]{0};
    bool *q = new bool[n]{0};
    for (int i = 0; i < n; i++)
    {
        dist[i] = szm[kp][i];
        ut[i] = kp;
        q[i] = false;
    }
    dist[kp] = 0;
    q[kp] = true;
    int cnt = 1;
    int kov = -1;
    while (cnt < n - 1)
    {
        int mindist = INF;
        for (int i = 0; i < n; i++)
        {
            if (dist[i] < mindist && !q[i])
            {
                mindist = dist[i];
                kov = i;
            }
        }
        if (kov == -1)
        {
            break;
        }
        q[kov] = true;
        for (int i = 0; i < n; i++)
        {
            if (!q[i])
            {
                if (mindist + szm[kov][i] < dist[i])
                {
                    dist[i] = mindist + szm[kov][i];
                    ut[i] = kov;
                }
            }
        }
        cnt++;
    }
    for (int i = 0; i < n; i++)
    {
        if (i == kp)
            continue;
        if (dist[i] != INF)
        {
            cout << "legrovidebb ut hossza " << i << "-be: " << dist[i] << endl;
            cout << "legrovidebb ut " << i << "-be: " << i;
            int s = i;
            do
            {
                s = ut[s];
                cout << " <- " << s;
            } while (s != kp);
        }
        else
        {
            cout << "legrovidebb ut hossza " << i << "-be: nem elerheto" << endl;
            cout << "legrovidebb ut " << i << "-be: nem elerheto";
        }
        cout << endl;
    }
    delete[] dist;
    delete[] ut;
    delete[] q;
}