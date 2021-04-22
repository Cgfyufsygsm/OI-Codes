#include <cstdio>
#include <cctype>
#include <algorithm>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

inline int read()
{
    bool w=0;
    int x=0;
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

inline int min(int a,int b)
{
    return a<b?a:b;
}

inline void swap(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
}

const int maxn=1e4+5,maxm=5e4+5;
int bin[maxn];

struct edge
{
    int u,v,w,next;
}e[maxn<<1],init[maxm];

int head[maxn],cnt;

inline void add(int u,int v,int w)
{
    e[++cnt].v=v;
    e[cnt].u=u;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
    return;
}

struct cmp
{
    bool operator()(const edge &a,const edge &b)
    {
        return a.w>b.w;
    }
};

int find(int x)
{
    if(x==bin[x])
        return x;
    return bin[x]=find(bin[x]);
}

bool query(int u,int v)
{
    return find(u)==find(v);
}

void uni(int u,int v)
{
    bin[find(u)]=find(v);
}

int n,m,q;

int dfn[maxn],vis[maxn],top[maxn],size[maxn],son[maxn],sonw[maxn],dep[maxn],fa[maxn],times,w[maxn];
int f[maxn<<2];

void dfs1(int u,int father,int d)
{
    vis[u]=1;
    size[u]=1;
    dep[u]=d;
    fa[u]=father;
    int maxson=-1;
    for(int i=head[u];i;i=e[i].next)
    {
        int &v=e[i].v;
        if(v==father)
            continue;
        dfs1(v,u,d+1);
        size[u]+=size[v];
        if(size[v]>maxson)
            maxson=size[v],son[u]=v,sonw[u]=e[i].w;
    }
    return;
}

void dfs2(int u,int topf,int wlast)
{
    top[u]=topf;
    dfn[u]=++times;
    w[dfn[u]]=wlast;
    if(son[u])
        dfs2(son[u],topf,sonw[u]);
    for(int i=head[u];i;i=e[i].next)
    {
        int &v=e[i].v;
        if(v==fa[u] || v==son[u])
            continue;
        dfs2(v,v,e[i].w);
    }
}

void build(int i,int j,int k)
{
    if(i==j)
    {
        f[k]=w[i];
        return;
    }
    build(i,M,L);
    build(M+1,j,R);
    f[k]=min(f[L],f[R]);
    return;
}

int query(int i,int j,int k,int x,int y)
{
    if(x>y)
        return 0x3f3f3f3f;
    if(x<=i && y>=j)
        return f[k];
    int ret=0x3f3f3f3f;
    if(x<=M)
        ret=min(ret,query(i,M,L,x,y));
    if(y>M)
        ret=min(ret,query(M+1,j,R,x,y));
    return ret;
}

int minask(int u,int v)
{
    int ret=0x3f3f3f3f;
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]])
            swap(u,v);
        ret=min(ret,query(1,n,1,dfn[top[u]],dfn[u]));
        u=fa[top[u]];
    }
    if(dep[u]>dep[v])
        swap(u,v);
    ret=min(ret,query(1,n,1,dfn[u]+1,dfn[v]));
    return ret;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
        init[i].u=read(),init[i].v=read(),init[i].w=read();
    std::sort(init+1,init+m+1,cmp());
    for(int i=1;i<=n;i++)
        bin[i]=i;
    for(int i=1;i<=m;i++)
    {
        if(!query(init[i].u,init[i].v))
        {
            add(init[i].u,init[i].v,init[i].w);
            add(init[i].v,init[i].u,init[i].w);
            uni(init[i].u,init[i].v);
        }
    }
    int q=read();
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            dfs1(i,0,1);
            dfs2(i,i,0);
        }
    }
    build(1,n,1);
    while(q--)
    {
        int x=read(),y=read();
        if(!query(x,y))
        {
            printf("-1\n");
            continue;
        }
        printf("%d\n",minask(x,y));
    }
    return 0;
}