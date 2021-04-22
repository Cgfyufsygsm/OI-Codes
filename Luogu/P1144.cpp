#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

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

const int maxn=1000000+5,maxm=2000000+5,mod=100003;

struct edge
{
    int from,to,w,nxt;
}e[maxm<<1];

int n,cnt,head[maxn];

inline void add(int u,int v,int w)
{
    e[++cnt].to=v;
    e[cnt].from=u;
    e[cnt].w=w;
    e[cnt].nxt=head[u];
    head[u]=cnt;
    return;
}

int dis[maxn],f[maxn];
bool vis[maxn];

int main()
{
    memset(dis,0x3f,sizeof dis);
    n=read();
    int m=read(),i,j;
    while(m--)
    {
        i=read(),j=read();
        add(i,j,1);
        add(j,i,1);
    }
    f[1]=1,dis[1]=0;
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
    q.push(make_pair(0,1));
    while(!q.empty())
    {
        int u=q.top().second;
        q.pop();
        if(vis[u])
            continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt)
        {
            int v=e[i].to;
            if(dis[u]+e[i].w<dis[v])
            {
                dis[v]=dis[u]+e[i].w;
                f[v]=f[u]%mod;
                q.push(make_pair(dis[v],v));
            }
            else if(dis[u]+e[i].w==dis[v])
                f[v]=(f[u]+f[v])%mod;
        }
    }
    for(int i=1;i<=n;i++)
        printf("%d\n",f[i]);
    return 0;
}