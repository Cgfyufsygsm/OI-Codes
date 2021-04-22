#include <cstdio>
#include <cctype>


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

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=1e6+5;

int head[maxn],to[maxn<<1],next[maxn<<1],cnt;

inline void add(int u,int v)
{
    to[++cnt]=v;
    next[cnt]=head[u];
    head[u]=cnt;
}

int n,size[maxn];
long long f[maxn],ans,maxd;

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
        f[v]=f[u]-(size[v]<<1)+size[1];
        if(f[v]>=maxd)
            maxd=f[v],ans=v;
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
    dfs2(1,0);
    printf("%d\n",maxd>f[1]?ans:1);
    return 0;
}