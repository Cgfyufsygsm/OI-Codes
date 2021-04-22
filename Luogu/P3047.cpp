#include <cstdio>
#include <cctype>

inline int read()
{
    int s=0;
    char c=getchar();
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=10*s+c-'0',c=getchar();
    return s;
}

const int maxn=1e5+5,maxk=23;
int head[maxn],to[maxn<<1],next[maxn<<1],cnt;
int n,k,c[maxn],f[maxn][maxk],g[maxn][maxk],dep[maxn];

inline void add(int u,int v)
{
    to[++cnt]=v;
    next[cnt]=head[u];
    head[u]=cnt;
}

void dfs1(int u,int fa)
{
    for(int kk=0;kk<=k;kk++)
        g[u][kk]=c[u];
    for(int i=head[u];i;i=next[i])
    {
        int v=to[i];
        if(v==fa)
            continue;
        dfs1(v,u);
        for(int kk=1;kk<=k;kk++)
            g[u][kk]+=g[v][kk-1];
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
        f[v][0]=c[v];
        for(int kk=1;kk<=k;kk++)
            f[v][kk]=f[u][kk-1]+g[v][kk]-(kk-2>=0?g[v][kk-2]:0);
        dfs2(v,u);
    }
    return;
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=n;i++)
        c[i]=read();
    dfs1(1,0);
    for(int i=0;i<=k;i++)
        f[1][i]=g[1][i];
    dfs2(1,0);
    for(int i=1;i<=n;i++)
        printf("%d\n",f[i][k]);
    return 0;
}