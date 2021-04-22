#include <cstdio>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;
int board[4][4];
int nxt[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
map<int,int> vis;
map<int,int> step;

inline int encode()
{
    int tmp=0;
    for(int i=1;i<4;i++)
        for(int j=1;j<4;j++)
        {
            tmp*=10;
            tmp+=board[i][j];
        }
    return tmp;
}

inline void decode(int code)
{
    int tmp=1e8;
    for(int i=1;i<4;i++)
        for(int j=1;j<4;j++)
        {
            board[i][j]=code/tmp;
            code%=tmp;
            tmp/=10;
            //printf("%d ",board[i][j]);
        }
    return;
}

inline void getxy(int &x0,int &y0)
{
    for(int i=1;i<4;i++)
        for(int j=1;j<4;j++)
            if(board[i][j]==0)
            {
                x0=i;
                y0=j;
                return;
            }
}

inline bool chkboard(int x,int y)
{
    if(x<1||y<1||x>3||y>3)
        return false;
    return true;
}

int bfs(int fst)
{
    queue<int> q;
    q.push(fst);
    q.push(123804765);
    vis[fst]=1;
    step[fst]=0;
    vis[123804765]=2;
    step[123804765]=0;
    while(!q.empty())
    {
        int cur=q.front();
        decode(cur);
        q.pop();
        int x0,y0;
        getxy(x0,y0);
        for(int k=0;k<4;k++)
        {
            int xx=x0+nxt[k][0],yy=y0+nxt[k][1];
            if(!chkboard(xx,yy)) continue;
            swap(board[xx][yy],board[x0][y0]);
            int now=encode();
            if(vis[now]==vis[cur])
            {
                swap(board[xx][yy],board[x0][y0]);
                continue;
            }
            if(vis[now]+vis[cur]==3)
            {
                return step[now]+step[cur]+1;
            }
            vis[now]=vis[cur];
            step[now]=step[cur]+1;
            q.push(now);
            swap(board[xx][yy],board[x0][y0]);
        }
    }
    return -1;
}

int main()
{
    int fst;
#ifndef ONLINE_JUDGE
    freopen("1379.in","r",stdin);
#endif
    scanf("%d",&fst);
    //printf("%d",fst);
    if(fst==123804765)
    {
        printf("0\n");
        return 0;
    }
    printf("%d\n",bfs(fst));
    return 0;
}