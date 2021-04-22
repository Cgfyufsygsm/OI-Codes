#include <cstdio>
#include <cctype>

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

void swap(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
    return;
}

const int maxn=50005;
int a[maxn],n,k;
int head[maxn],to[maxn<<1],next[maxn<<1],cnt;
int top[maxn],dep[maxn],son[maxn],size[maxn],fa[maxn];
int ans;

void dfs1(int u,int father,int d)
{
    fa[u]=father;
    dep[u]=d;
    size[u]=1;
    int maxson=-1;
    for(int i=head[u];i;i=next[i])
    {
        int &v=to[i];
        if(v==father)
            continue;
        dfs1(v,u,d+1);
        size[u]+=size[v];
        if(size[v]>maxson)
            son[u]=v,maxson=size[v];
    }
    return;
}

void dfs2(int u,int topf)
{
    top[u]=topf;
    if(son[u])
        dfs2(son[u],topf);
    for(int i=head[u];i;i=next[i])
    {
        int &v=to[i];
        if(v==fa[u] || v==son[u])
            continue;
        dfs2(v,v);
    }
    return;
}

inline void add(int u,int v)
{
    to[++cnt]=v;
    next[cnt]=head[u];
    head[u]=cnt;
    return;
}

int lca(int u,int v)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]])
            swap(u,v);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v])
        swap(u,v);
    return u;
}

void stat(int u)
{
    for(int i=head[u];i;i=next[i])
    {
        int &v=to[i];
        if(v==fa[u])
            continue;
        stat(v);
        a[u]+=a[v];
    }
    ans=ans<a[u]?a[u]:ans;
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
    dfs1(1,0,1);
    dfs2(1,1);
    while(k--)
    {
        int u=read(),v=read();
        ++a[u],++a[v];
        int LCA=lca(u,v);
        --a[fa[LCA]],--a[LCA];
    }
    stat(1);
    printf("%d\n",ans);
    return 0;
}