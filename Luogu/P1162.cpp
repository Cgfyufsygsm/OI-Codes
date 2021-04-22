#include <iostream>
#include <queue>
using namespace std;
int maze[50][50],n;
bool vis[30][30]={0};
void bfs(int,int);
struct node
{
    int x,y;
};
int main()
{
    cin>>n;
    for(int y=1;y<=n;y++)
    {
        for(int x=1;x<=n;x++)
        {
            int t;
            cin>>t;
            if(t==1)
                maze[x][y]=1;
            else
                maze[x][y]=2;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(maze[1][i]==2&&!vis[1][i]) bfs(1,i);
        if(maze[i][1]==2&&!vis[i][1]) bfs(i,1);
        if(maze[n][i]==2&&!vis[n][i]) bfs(n,i);
        if(maze[i][n]==2&&!vis[i][n]) bfs(i,n);
    }
    for(int y=1;y<=n;y++)
    {
        for(int x=1;x<=n;x++)
        {
            cout<<maze[x][y]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
void bfs(int x,int y)
{
    queue<node> q;
    q.push((node){x,y});
    vis[x][y]=1;
    maze[x][y]=0;
    int next[][2]={{0,1},{1,0},{0,-1},{-1,0}};
    while(!q.empty())
    {
        int x=q.front().x,y=q.front().y;
        for(int k=0;k<4;k++)
        {
            int tx=x+next[k][0],ty=y+next[k][1];
            if(tx<1||tx>n||ty<1||ty>n)
                continue;
            if(!vis[tx][ty]&&maze[tx][ty]==2)
            {
                vis[tx][ty]=1;
                maze[tx][ty]=0;
                q.push((node){tx,ty});
            }
            else
                continue;
        }
        q.pop();
    }
    return;
}