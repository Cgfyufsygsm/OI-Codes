#include <string>
#include <queue>
#include <iostream>
#include <cstring>

using namespace std;

string maze_name;
int r0,c0,r1,c1,r2,c2;
char dir0;

struct node
{
    int r,c,dir;
    node(){}
    node(int _r,int _c,int _dir)
    {
        r=_r,c=_c,dir=_dir;
    }
};

const char* dirs="NESW";
const char* turns="FLR";

inline int dir_id(char c)
{
    return strchr(dirs,c)-dirs;
}

inline int turn_id(char c)
{
    return strchr(turns,c)-turns;
}

inline bool chk(int r,int c)
{
    return 1<=r && r<=9 && 1<=c && c<=9;
}

const int dr[] = {-1,0,1,0};
const int dc[] = {0,1,0,-1};

bool has_edge[10][10][4][4];
node p[10][10][4];
int d[10][10][4];


inline node walk(const node &now,int turn)
{
    int dir=now.dir;
    if(turn==1)
        dir=(dir+3)%4;
    else if(turn==2)
        dir=(dir+1)%4;
    return node(now.r+dr[dir],now.c+dc[dir],dir);
}

void print(node u)
{
    vector<node> way;
    while(true)
    {
        way.push_back(u);
        if(!d[u.r][u.c][u.dir])
            break;
        u=p[u.r][u.c][u.dir];
    }
    way.push_back(node(r0,c0,dir_id(dir0)));
    int cnt=0;
    for(int i=way.size()-1;i>=0;i--)
    {
        if(cnt%10==0)
            cout<<' ';
        cout<<" ("<<way[i].r<<','<<way[i].c<<')';
        if(++cnt%10==0)
            cout<<endl;
    }
    if(way.size()%10)
        cout<<endl;
    return;
}

void bfs()
{
    cout<<maze_name<<endl;
    queue<node> q;
    memset(d,-1,sizeof d);
    memset(p,0,sizeof p);
    q.push(node(r1,c1,dir_id(dir0)));
    d[r1][c1][dir_id(dir0)]=0;
    while(!q.empty())
    {
        node now=q.front();
        q.pop();
        if(now.r==r2 && now.c==c2)
        {
            print(now);
            return;
        }
        for(int i=0;i<3;i++)//枚举转弯的方向
        {
            node to=walk(now,i);//转个弯
            if(has_edge[now.r][now.c][now.dir][i] && chk(to.r,to.c) && d[to.r][to.c][to.dir]<0)//判断是否合法
            {
                d[to.r][to.c][to.dir]=d[now.r][now.c][now.dir]+1;
                p[to.r][to.c][to.dir]=now;
                q.push(to);
            }
        }
    }
    cout<<"  No Solution Possible"<<endl;
}

bool read_maze()
{
    memset(has_edge,0,sizeof has_edge);
    cin>>maze_name;
    if(maze_name=="END")
        return false;
    cin>>r0>>c0>>dir0>>r2>>c2;
    r1=r0+dr[dir_id(dir0)];
    c1=c0+dc[dir_id(dir0)];
    int r,c;
    string tmp;
    while(true)
    {
        cin>>r;
        if(!r)
            break;
        cin>>c>>tmp;
        while(tmp!="*")
        {
            int dir=dir_id(tmp[0]);
            for(int i=1;i<tmp.size();i++)
                has_edge[r][c][dir][turn_id(tmp[i])]=true;
            cin>>tmp;
        }
    }
    bfs();
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    while(read_maze());
    return 0;
}