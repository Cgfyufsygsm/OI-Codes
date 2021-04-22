#include <queue>
#include <cstdio>
#include <vector>
#include <cctype>
#include <utility>
#include <cstring>

using namespace std;

const int maxn=1e3+5;

struct node
{
    int pos,f;
    node(){}
    node(int _p,int _f)
    {
        pos=_p;
        f=_f;
    }
};

struct edge
{
    int from,to,dist;
    edge(){}
    edge(int u,int v,int w)
    {
        from=u;
        to=v;
        dist=w;
    }
};

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
    {
        if(c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

vector<edge> g1[maxn],g2[maxn];
int dis[maxn],n,m,k;
bool vis[maxn];

bool operator<(const node &_a,const node &_b)
{
    return _a.f+dis[_a.pos]>_b.f+dis[_b.pos];
}

void dijsktra()
{
    priority_queue<pair<int,int>, vector<pair<int,int> >,greater<pair<int,int> > > q;
    memset(dis,0x3f,sizeof(vis));
    dis[1]=0;
    q.push(make_pair(0,1));
    while(!q.empty())
    {
        int now=q.top().second;
        q.pop();
        
        if(!vis[now])
        {
            vis[now]=1;
            for(auto &e:g2[now])
            {
                if(dis[e.to]>dis[now]+e.dist)
                {
                    dis[e.to]=dis[now]+e.dist;
                    q.push(make_pair(dis[e.to],e.to));
                }
            }
        }
    }
    return;
}

void astar()
{
    priority_queue<node> q;
    q.push(node(n,0));
    while(!q.empty())
    {
        int now=q.top().pos,f=q.top().f;
        q.pop();
        if(now==1)
        {
            printf("%lld\n",f);
            if(!(--k))
                return;
        }
        else
            for(auto i:g1[now])
                q.push(node(i.to,i.dist+f));
    }
    while(k--)
        printf("-1\n");
    return;
}

inline void ins(int u,int v,int w)
{
    g1[u].push_back(edge(u,v,w));
    g2[v].push_back(edge(v,u,w));
    return;
}

int main()
{
    n=read(),m=read(),k=read();
    int u,v,w;
    for(int i=1;i<=m;i++)
    {
        u=read(),v=read(),w=read();
        ins(u,v,w);
    }
    dijsktra();
    astar();
    return 0;
}