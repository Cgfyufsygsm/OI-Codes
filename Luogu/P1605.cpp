#include <iostream>
using namespace std;
bool maze[6][6] = {0}, book[6][6] = {0};
int n, m, t, sx, sy, fx, fy, tot = 0;

void dfs(int x, int y);
int main()
{
    cin >> n >> m >> t;
    cin >> sx >> sy >> fx >> fy;
    for (int i = 1; i <= t; i++)
    {
        int tx, ty;
        cin >> tx >> ty;
        maze[tx][ty] = 1;
    }
    book[sx][sy] = 1;
    dfs(sx, sy);
    cout << tot << endl;
    return 0;
}

void dfs(int x, int y)
{
    if (x == fx && y == fy)
    {
        tot++;
        return;
    }
    else
    {
        for (int i = 1; i <= 4; i++)
        {
            int tx = x, ty = y;
            switch (i)
            {
            case 1:
                tx++;
                break;
            case 2:
                tx--;
                break;
            case 3:
                ty++;
                break;
            case 4:
                ty--;
                break;
            }
            if (tx < 1 || tx > n || ty < 1 || ty > m)
            {
                continue;
            }
            if ((!maze[tx][ty]) && (!book[tx][ty]))
            {
                book[tx][ty] = 1;
                dfs(tx, ty);
                book[tx][ty] = 0;
            }
        }
        return;
    }
}