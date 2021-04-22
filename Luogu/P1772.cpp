#include <cstdio>
#include <cctype>
#include <queue>
#include <cstring>
#include <utility>

typedef long long ll;
const int maxn=105;
ll G[21][21],f[105];
ll avl[21][105];
bool now[21];
int n,m,k,e;

ll dij()
{
    std::priority_queue<std::pair<ll,int>,std::vector<std::pair<ll,int> >,std::greater<std::pair<ll,int> > > q;
    ll dis[21];
    memset(dis,0x3f,sizeof dis);
    q.push(std::make_pair(0,1));
    dis[1]=0;
    bool vis[21];
    memset(vis,0,sizeof vis);
    while(!q.empty())
    {
        int u=q.top().second;q.pop();
        if(!vis[u])
        {
            vis[u]=1;
            for(int v=1;v<=m;v++)
            {
                if(G[u][v]<0x3f3f3f3f && (!now[v]) && v!=u)
                {
                    if(dis[u]+G[u][v]<dis[v])
                    {
                        dis[v]=dis[u]+G[u][v];
                        q.push(std::make_pair(dis[v],v));
                    }
                }
            }
        }
    }
    return dis[m];
}

int main()
{
    memset(G,0x3f,sizeof G);
    scanf("%d %d %d %d",&n,&m,&k,&e);
    while(e--)
    {
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        G[u][v]=G[v][u]=w;
    }
    int d;
    scanf("%d",&d);
    while(d--)
    {
        int p,a,b;
        scanf("%d %d %d",&p,&a,&b);
        for(int i=a;i<=b;i++)
            avl[p][i]=1;
    }
    memset(f,0x3f,sizeof f);
    f[0]=-k;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            now[j]=0;
        for(int j=i;j>=1;j--)
        {
            for(int u=1;u<=m;u++)
                if(avl[u][j])
                    now[u]=1;
            ll dis=dij();
            if(dis>=0x3f3f3f3f)
                break;
            f[i]=std::min(f[i],f[j-1]+(i-j+1)*dis+k);
        }
    }
    printf("%lld\n",f[n]);
    return 0;
}