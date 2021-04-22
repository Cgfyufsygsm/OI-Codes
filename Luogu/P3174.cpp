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

inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}

const int maxn=300000+5;
int n;
int deg[maxn];
int head[maxn],to[maxn<<1],nxt[maxn<<1],cnt;
int ans,f[maxn],g[maxn];

inline void add(int u,int v)
{
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
    return;
}

void dfs1(int u,int fa)
{
    if(fa)deg[u]=1;
    g[u]=1;
    int tmp=-1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa)continue;
        dfs1(v,u);
        tmp=max(tmp,g[v]);
        ++deg[u];
    }
    if(deg[u]!=1)
        g[u]=tmp+deg[u]-1;
    if(!fa)g[u]++;
    return;
}

void dfs2(int u,int fa)
{
    int tmp1=-1,tmp2=-1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa)continue;
        dfs2(v,u);
        if(g[v]>tmp1)
        {
            tmp2=tmp1;
            tmp1=g[v];
        }
        else if(g[v]>tmp2 && g[v]<tmp1)
            tmp2=g[v];
    }
    if(deg[u]>2)
        f[u]=tmp1+tmp2+deg[u]-1;
    f[u]=max(f[u],g[u]);
    ans=max(ans,f[u]);
    return;
}

int main()
{
    n=read();int m=read();
    if(n==1)
    {
        printf("1\n");
        return 0;
    }
    while(m--)
    {
        int u=read(),v=read();
        add(u,v);
        add(v,u);
    }
    dfs1(1,0);
    dfs2(1,0);
    printf("%d\n",ans);
    return 0;
}