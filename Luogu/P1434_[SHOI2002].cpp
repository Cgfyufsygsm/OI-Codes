#include <iostream>
#define max(a,b) a>b?a:b
using namespace std;
int r,c,maze[101][101]={0},ans[101][101]={0};
int dfs(int,int);
int main()
{
    cin>>r>>c;
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            cin>>maze[i][j];
        }
    }
    int maxn=0;
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            maxn=max(dfs(i,j),maxn);
        }
    }
    cout<<maxn<<endl;
}
int dfs(int x,int y)
{
    if(ans[x][y])
        return ans[x][y];
    int nxt[][2]={{1,0},{-1,0},{0,1},{0,-1}};
    ans[x][y]=1;
    for(int k=0;k<4;k++)
    {
        int tx=x+nxt[k][0],ty=y+nxt[k][1];
        if(tx<1||tx>r||ty<1||ty>c) continue;
        if(maze[tx][ty]<maze[x][y])
        {
            ans[x][y]=max(dfs(tx,ty)+1,ans[x][y]);
        }
    }
    return ans[x][y];
}