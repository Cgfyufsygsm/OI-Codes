#include <cstdio>
using namespace std;
char maze[101][101] = {0},word[]="yizhong";
int n;
bool vis[101][101] = {0};
int dir[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

bool dfs(int x,int y,int step,int k)
{
    if(step<7)
    {
        if(maze[x][y]==word[step])
        {
            if(dfs(x+dir[k][0],y+dir[k][1],step+1,k))
            {
                vis[x][y]=1;
                return 1;
            }
            else
                return 0;
        }
        else
            return 0;
        
    }
    else
        return 1;
}

int main()
{
    scanf("%d", &n);
    for (int x = 1; x <= n; x++)
        scanf("%s", maze[x] + 1);
    for(int x=1;x<=n;x++)
    {
        for(int y=1;y<=n;y++)
        {
            if(maze[x][y]=='y')
            {
                for(int k=0;k<8;k++)
                {
                    int tx=x,ty=y;
                    tx+=dir[k][0];
                    ty+=dir[k][1];
                    if(maze[tx][ty]=='i')
                        dfs(x,y,0,k);
                }
            }
        }
    }
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            if (vis[x][y])
                putchar(maze[x][y]);
            else
                putchar('*');
        }
        putchar('\n');
    }
    return 0;
}