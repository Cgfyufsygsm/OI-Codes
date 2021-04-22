#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int n, m;
int d = 0; //d表示连通图当前的个数
char maze[1500][1500];
int flag[1500][1500] = {0}; //flag标记某个点在第n个连通图中
int ans[1000000];           //ans标记连通图大小
struct node
{
    int x, y;
    char c;
};
int bfs(int, int);
int main()
{
    memset(ans, 1, sizeof(ans));
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> maze[i][j];
        }
    }
    for (int i = 1; i <= m; i++)
    {
        int tx, ty;
        cin >> tx >> ty;
        cout << bfs(tx, ty) << endl;
    }
    return 0;
}
int bfs(int sx, int sy)
{
    if (flag[sx][sy])
        return ans[flag[sx][sy]];
    else
    {
        d++;
        queue<node> q;
        flag[sx][sy] = d;
        int sum = 1;
        q.push((node){sx, sy, maze[sx][sy]});
        int nxt[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        while (!q.empty())
        {
            int x = q.front().x, y = q.front().y, c = q.front().c;
            for (int k = 0; k < 4; k++)
            {
                int tx = x + nxt[k][0], ty = y + nxt[k][1];
                if (tx > 0 && tx <= n && ty > 0 && ty <= n && (!flag[tx][ty]) && maze[tx][ty] != maze[x][y])
                {
                    flag[tx][ty] = d;
                    sum++;
                    q.push((node){tx, ty, maze[tx][ty]});
                }
            }
            q.pop();
        }
        ans[d]=sum;
        return ans[flag[sx][sy]];
    }
}