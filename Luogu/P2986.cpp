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

inline ll min(ll a,ll b)
{
    return a<b?a:b;
}

const int maxn=1e5+5;

int head[maxn],to[maxn<<1],next[maxn<<1],cnt;
ll w[maxn<<1];

inline void add(int u,int v,ll _w)
{
    to[++cnt]=v;
    next[cnt]=head[u];
    w[cnt]=_w;
    head[u]=cnt;
}

int n;
ll c[maxn],f[maxn],size[maxn],ans;

void dfs1(int u,int fa)
{
    size[u]=c[u];
    for(int i=head[u];i;i=next[i])
    {
        int v=to[i];
        if(v==fa)
            continue;
        dfs1(v,u);
        size[u]+=size[v];
        f[1]+=size[v]*w[i];
    }
    return;
}

void dfs2(int u,int fa)
{
    for(int i=head[u];i;i=next[i])
    {
        int v=to[i];
        if(v==fa)
            continue;
        f[v]=f[u]-w[i]*size[v]+w[i]*(size[1]-size[v]);
        ans=min(ans,f[v]);
        dfs2(v,u);
    }
    return;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        c[i]=read();
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read(),l=read();
        add(u,v,l);
        add(v,u,l);
    }
    ans=1e18;
    dfs1(1,0);
    dfs2(1,0);
    printf("%lld\n",min(f[1],ans));
    return 0;
}