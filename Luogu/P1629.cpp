#include <cstdio>
#include <queue>
#include <cstring>
#include <utility>
using namespace std;

const int maxn=1005;
int n,m;

struct edge
{
    int from,to,dist;
    edge(){}
    edge(int u,int v,int w)
    {
        from=u,to=v,dist=w;
    }
};

struct graph
{
    vector<edge> g[maxn];
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;
    int d[maxn];
    bool vis[maxn];
    void ins(int u,int v,int w)
    {
        g[u].push_back(edge(u,v,w));
        return;
    }
    void dijkstra()
    {
        memset(d,0x3f3f3f3f,sizeof(d));
        memset(vis,false,sizeof(vis));
        d[1]=0;
        q.push(make_pair(0,1));
        while(!q.empty())
        {
            int now=q.top().second;
            q.pop();
            if(!vis[now])
            {
                vis[now]=true;
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
    }
}a,b;

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        a.ins(u,v,w);
        b.ins(v,u,w);
    }
    a.dijkstra(),b.dijkstra();
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=a.d[i];
        ans+=b.d[i];
    }
    printf("%d\n",ans);
    return 0;
}