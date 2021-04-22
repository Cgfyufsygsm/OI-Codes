#include <cstdio>
#include <cctype>

typedef long long ll;

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

inline ll max(ll a,ll b)
{
    return a>b?a:b;
}

const int maxn=2e5+5;

int head[maxn],to[maxn<<1],next[maxn<<1],cnt;

inline void add(int u,int v)
{
    to[++cnt]=v;
    next[cnt]=head[u];
    head[u]=cnt;
}

int n;
long long size[maxn],f[maxn],g[maxn],ans,maxd;

void dfs1(int u,int fa)
{
    size[u]=1;
    for(int i=head[u];i;i=next[i])
    {
        int v=to[i];
        if(v==fa)
            continue;
        dfs1(v,u);
        size[u]+=size[v];
        g[u]+=g[v];
    }
    g[u]+=size[u];
    return;
}

void dfs2(int u,int fa)
{
    for(int i=head[u];i;i=next[i])
    {
        int v=to[i];
        if(v==fa)
            continue;
        f[v]=f[u]-(size[v]<<1)+size[1];
        ans=max(ans,f[v]);
        dfs2(v,u);
    }
    return;
}

int main()
{
    n=read();
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    f[1]=g[1];
    dfs2(1,0);
    printf("%lld\n",max(f[1],ans));
    return 0;
}