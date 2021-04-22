#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

const int maxn=2505;

struct edge
{
    int from,to,dist;
    edge(){}
    edge(int u,int v,int w)
    {
        from=u,to=v,dist=w;
    }
};

bool operator>(const edge &a,const edge &b)
{
    return a.dist<b.dist;
}

vector<edge> g[maxn];
int n,m,s,t;
priority_queue<pair<int,int>, vector<pair<int,int> >,greater<pair<int,int> > > q;
bool vis[maxn];
int d[maxn];

void ins(int u,int v,int w)
{
    g[u].push_back(edge(u,v,w));
    g[v].push_back(edge(v,u,w));
    return;
}

int dij()
{
    memset(d,0x3f3f3f3f,sizeof(d));
    d[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
    {
        int now=q.top().second;
        q.pop();
        if(!vis[now])
        {
            vis[now]=1;
            for(auto &e:g[now])
            {
                if(d[e.to]>d[now]+e.dist)
                {
                    d[e.to]=d[now]+e.dist;
                    q.push(make_pair(d[e.to],e.to));
                }
            }
        }
    }
    return d[t];
}

int main()
{
    scanf("%d %d %d %d",&n,&m,&s,&t);
    int u,v,w;
    for(int i=1;i<=m;++i)
    {
        scanf("%d %d %d",&u,&v,&w);
        ins(u,v,w);
    }
    printf("%d\n",dij());
    return 0;
}