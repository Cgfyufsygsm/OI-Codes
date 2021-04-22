#include <cstdio>
#include <queue>
using namespace std;

int n,m;
//n is line, m is col
int sx,sy,fx,fy;
int maze[52][52];
int kln[4][4],kcol[4][4];
//the first dimension 0-3 is ESWN,the second is the step
bool vis[52][52][4];//存储每个点的方向是否访问过

struct node
{
    int x,y;//机器人左上角坐标
    int face;//目前的朝向
    int step;//目前已经走的时间
    node(){}
    node(int _x,int _y,int _face,int _step)
    {
        x=_x;
        y=_y;
        face=_face;
        step=_step;
    }
};

queue<node> q;

void updk()
{
    kln[1][1]=1,kln[1][2]=2,kln[1][3]=3;
    kln[3][1]=-1,kln[3][2]=-2,kln[3][3]=-3;
    kln[0][1]=kln[0][2]=kln[0][3]=0;
    kln[2][1]=kln[2][2]=kln[2][3]=0;
    kcol[1][1]=kcol[1][2]=kcol[1][3]=0;
    kcol[3][1]=kcol[3][2]=kcol[3][3]=0;
    kcol[0][1]=1,kcol[0][2]=2,kcol[0][3]=3;
    kcol[2][1]=-1,kcol[2][2]=-2,kcol[2][3]=-3;
    return;
}

inline bool isvalid(int x,int y)
{
    if(x<1||x>n-1||y<1||y>m-1)
        return false;
    if(maze[x][y]||maze[x+1][y]||maze[x+1][y+1]||maze[x][y+1])
        return false;
    return true;
}

int bfs()
{
    int ans=0x3f3f3f3f;
    bool flag=0;
    while(!q.empty())
    {
        int nowx=q.front().x,nowy=q.front().y,nowdir=q.front().face,nowstep=q.front().step;
        q.pop();
        if(!isvalid(nowx,nowy))
            continue;
        if(nowx==fx && nowy==fy)
        {
            ans=nowstep<ans?nowstep:ans;
            flag=1;
        }
        if(!vis[nowx][nowy][(nowdir+1)%4])
        {
            vis[nowx][nowy][(nowdir+1)%4]=1;
            q.push(node(nowx,nowy,(nowdir+1)%4,nowstep+1));
        }
        if(!vis[nowx][nowy][(nowdir+3)%4])
        {
            vis[nowx][nowy][(nowdir+3)%4]=1;
            q.push(node(nowx,nowy,(nowdir+3)%4,nowstep+1));
        }
        for(int s=1;s<=3;s++)
        {
            int xx=nowx+kln[nowdir][s],yy=nowy+kcol[nowdir][s];
            if(!isvalid(xx,yy))
                break;
            if(!vis[xx][yy][nowdir])
            {
                vis[xx][yy][nowdir]=1;
                q.push(node(xx,yy,nowdir,nowstep+1));
            }
        }
    }
    return flag?ans:-1;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&maze[i][j]);
    updk();
    char dir;
    scanf("%d %d %d %d %c",&sx,&sy,&fx,&fy,&dir);
    if(dir=='E') dir=0;
    if(dir=='S') dir=1;
    if(dir=='W') dir=2;
    if(dir=='N') dir=3;
    vis[sx][sy][dir]=1;
    q.push(node(sx,sy,dir,0));
    printf("%d\n",bfs());
    return 0;
}