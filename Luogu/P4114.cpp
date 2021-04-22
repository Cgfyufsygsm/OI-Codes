#include <cstdio>
#include <cctype>
#include <vector>

#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

using std::vector;

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

inline void swap(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
    return;
}

inline int max(int a,int b)
{
    return a>b?a:b;
}

struct edge
{
    int u,v,w,id;
    edge(){}
    edge(int f,int t,int d,int i)
    {
        u=f,v=t,w=d,id=i;
    }
};

const int maxn=1e5+5;

int n;
vector<edge> G[maxn];
int fa[maxn],size[maxn],dep[maxn],son[maxn],dfn[maxn],top[maxn],w[maxn],id[maxn];
int cnt;

int f[maxn<<2];

void build(int i,int j,int k)
{
    if(i==j)
    {
        f[k]=w[i];
        return;
    }
    build(i,M,L);
    build(M+1,j,R);
    f[k]=max(f[L],f[R]);
    return;
}

void modify(int i,int j,int k,int x,int d)
{
    if(i==j)
    {
        f[k]=d;
        return;
    }
    if(x<=M)
        modify(i,M,L,x,d);
    else
        modify(M+1,j,R,x,d);
    f[k]=max(f[L],f[R]);
    return;
}

int query(int i,int j,int k,int x,int y)
{
    if(x<=i && y>=j)
        return f[k];
    int ans=0;
    if(x<=M)
        ans=max(ans,query(i,M,L,x,y));
    if(y>M)
        ans=max(ans,query(M+1,j,R,x,y));
    return ans;
}

void dfs1(int u,int father,int depth)
{
    dep[u]=depth;
    fa[u]=father;
    size[u]=1;
    int maxson=-1;
    for(auto e:G[u])
    {
        int &v=e.v;
        if(v==fa[u])
            continue;
        dfs1(v,u,depth+1);
        size[u]+=size[v];
        if(maxson<size[v])
            son[u]=v,maxson=size[v];
    }
    return;
}

void dfs2(int u,int topf)
{
    dfn[u]=++cnt;
    top[u]=topf;
    if(son[u])
        dfs2(son[u],topf);
    for(auto e:G[u])
    {
        int &v=e.v;
        if(v==fa[u] || v==son[u])
            continue;
        dfs2(v,v);
    }
    return;
}

void dfs3(int u,edge last)
{
    w[dfn[u]]=last.w;
    id[last.id]=dfn[u];
    for(auto e:G[u])
    {
        if(e.v!=fa[u])
            dfs3(e.v,e);
    }
    return;
}

inline void modify(int i,int t)
{
    modify(1,n,1,id[i],t);
    return;
}

inline int query(int a,int b)
{
    int ans=0;
    while(top[a]!=top[b])
    {
        if(dep[top[a]]<dep[top[b]])
            swap(a,b);
        ans=max(ans,query(1,n,1,dfn[top[a]],dfn[a]));
        a=fa[top[a]];
    }
    if(dep[a]>dep[b])
        swap(a,b);
    ans=max(ans,query(1,n,1,dfn[a]+1,dfn[b]));
    return ans;
}

int main()
{
    n=read();
    int a,b,w;
    for(int i=1;i<n;i++)
    {
        a=read(),b=read(),w=read();
        G[a].push_back(edge(a,b,w,i));
        G[b].push_back(edge(b,a,w,i));
    }
    dfs1(1,0,1);
    dfs2(1,1);
    dfs3(1,edge(0,1,0,0));
    build(1,n,1);
    char s[7];
    while(1)
    {
        scanf("%s %d %d",s,&a,&b);
        if(s[0]=='D')
            return 0;
        else if(s[0]=='C')
            modify(a,b);
        else if(s[0]=='Q')
            printf("%d\n",query(a,b));
    }
    return 0;
}