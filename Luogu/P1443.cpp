#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
int maze[401][401] = {0};
struct node
{
    int x, y, step;
};
int dir[][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};
int n, m, sx, sy;
void bfs();
int main()
{
    memset(maze, -1, sizeof(maze));
    scanf("%d%d%d%d", &n, &m, &sx, &sy);
    bfs();
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= m; y++)
        {
            printf("%-5d", maze[x][y]);
        }
        putchar('\n');
    }
    return 0;
}
void bfs()
{
    queue<node> q;
    bool vis[401][401] = {0};
    q.push((node){sx, sy, 0});
    maze[sx][sy]=0;
    vis[sx][sy] = 1;
    while (!q.empty())
    {
        for (int i = 0; i < 8; i++)
        {
            int tx = q.front().x, ty = q.front().y;
            tx += dir[i][0];
            ty += dir[i][1];
            if (tx > n || tx < 1 || ty > m || ty < 1)
                continue;
            else if (vis[tx][ty])
                continue;
            else
            {
                vis[tx][ty] = 1;
                maze[tx][ty] = q.front().step+1;
                q.push((node){tx, ty, q.front().step + 1});
            }
        }
        q.pop();
    }
    return;
}
