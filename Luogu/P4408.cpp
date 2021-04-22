#include <cstdio>
#include <cctype>

typedef long long ll;
const int maxn=200000+5;

inline ll read()
{
    bool w=0;
    ll x=0;
    char c=getchar();
    while(!isdigit(c))
    {
        if(c=='-')
            w=1;
        c=getchar();
    }
    while(isdigit(c))
        x=x*10+c-'0',c=getchar();
    return w?-x:x;
}

inline ll max(ll a,ll b)
{
    return a>b?a:b;
}

inline ll min(ll a,ll b)
{
    return a<b?a:b;
}

struct edge
{
    int to,next;
    ll w;
}e[maxn<<1];

int cnt,head[maxn];

inline void add(int u,int v,ll w)
{
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}

int n,m;
int l1,l2;
ll dis[maxn][3],maxdis;

void dfs(int u,int fa,int opt)
{
    for(int i=head[u];i;i=e[i].next)
    {
        int &v=e[i].to;
        ll &w=e[i].w;
        if(v==fa)
            continue;
        dis[v][opt]=dis[u][opt]+w;
        dfs(v,u,opt);
    }
    if(dis[u][opt]>maxdis)
    {
        maxdis=dis[u][opt];
        if(opt==0)
            l1=u;
        else if(opt==1)
            l2=u;
    }
    return;
}

int main()
{
    n=read(),m=read();
    while(m--)
    {
        int u=read(),v=read();
        ll w=read();
        add(u,v,w);
        add(v,u,w);
    }
    maxdis=-1;
    dfs(1,0,0);
    maxdis=-1;
    dfs(l1,0,1);
    dfs(l2,0,2);
    ll tmp=-1;
    for(int i=1;i<=n;i++)
        tmp=max(tmp,min(dis[i][1],dis[i][2]));
    printf("%lld\n",tmp+dis[l2][1]);
    return 0;
}