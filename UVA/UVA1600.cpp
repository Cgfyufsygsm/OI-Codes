#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>

using std::queue;

const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

class UVA1600
{
private:
    int n,m,k,maze[25][25];
    bool vis[25][25][25];
    struct node
    {
        int x,y,k,step;
        node(){}
        node(int i,int j,int _k,int _step)
        {
            x=i;
            y=j;
            k=_k;
            step=_step;
        }
    };
    bool chk(int i,int j)
    {
        return i>=1 && i<=m && j>=1 && j<=n;
    }
    int bfs()
    {
        queue<node> q;
        q.push(node(1,1,0,0));
        vis[1][1][0]=0;
        while(!q.empty())
        {
            node now=q.front();
            q.pop();
            if(now.k>k)
                continue;
            if(now.x==m && now.y==n)
                return now.step;
            for(int i=0;i<4;i++)
            {
                int xx=now.x+dx[i],yy=now.y+dy[i],nowk=maze[xx][yy]?now.k+maze[xx][yy]:0;
                if((!chk(xx,yy)) || vis[xx][yy][nowk])
                    continue;
                vis[xx][yy][nowk]=1;
                q.push(node(xx,yy,nowk,now.step+1));
            }
        }
        return -1;
    }
public:
    void solve()
    {
        memset(vis,0,sizeof(vis));
        m=read(),n=read(),k=read();
        for(int i=1;i<=m;i++)
            for(int j=1;j<=n;j++)
                maze[i][j]=read();
        printf("%d\n",bfs());
    }
}s;

int main()
{
    //freopen("1.out","w",stdout);
    int t=read();
    while(t--)
        s.solve();
}