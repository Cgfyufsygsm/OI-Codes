#include <cstdio>
#include <cctype>
#include <vector>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

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

inline void swap(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
    return;
}

const int maxn=1e5+5;
int f[maxn<<2],tag[maxn<<2];
int n,m,cnt,fa[maxn],son[maxn],size[maxn],top[maxn],dep[maxn],id[maxn];
std::vector<int> G[maxn];

void dfs1(int u,int father,int d)
{
    dep[u]=d;
    size[u]=1;
    fa[u]=father;
    int maxson=-1;
    for(auto v:G[u])
    {
        if(v==fa[u])
            continue;
        dfs1(v,u,d+1);
        size[u]+=size[v];
        if(size[v]>maxson)
            maxson=size[v],son[u]=v;
    }
    return;
}

void dfs2(int u,int topf)
{
    top[u]=topf;
    id[u]=++cnt;
    if(son[u])
        dfs2(son[u],topf);
    for(auto v:G[u])
    {
        if(v==son[u] || v==fa[u])
            continue;
        dfs2(v,v);
    }
    return;
}

void down(int i,int j,int k)
{
    f[L]+=(M-i+1)*tag[k];
    f[R]+=(j-M)*tag[k];
    tag[L]+=tag[k],tag[R]+=tag[k];
    tag[k]=0;
    return;
}

void modify(int i,int j,int x,int y,int k)
{
    if(x>y)
        return;
    if(x<=i && y>=j)
    {
        f[k]+=(j-i+1);
        tag[k]++;
        return;
    }
    if(tag[k])
        down(i,j,k);
    if(x<=M)
        modify(i,M,x,y,L);
    if(y>M)
        modify(M+1,j,x,y,R);
    f[k]=f[L]+f[R];
    return;
}

void modify(int a,int b)
{
    while(top[a]!=top[b])
    {
        if(dep[top[a]]<dep[top[b]])
            swap(a,b);
        modify(1,n,id[top[a]],id[a],1);
        a=fa[top[a]];
    }
    if(dep[a]>dep[b])
        swap(a,b);
    modify(1,n,id[a]+1,id[b],1);
    return;
}

int query(int i,int j,int x,int k)
{
    if(i==j)
        return f[k];
    if(tag[k])
        down(i,j,k);
    if(x<=M)
        return query(i,M,x,L);
    else
        return query(M+1,j,x,R);
}

int query(int a,int b)
{
    if(a==fa[b])
        return query(1,n,id[b],1);
    else
        return query(1,n,id[a],1);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++)
    {
        int a=read(),b=read();
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs1(1,0,1);
    dfs2(1,1);
    while(m--)
    {
        char c;
        int a,b;
        scanf("\n%c %d %d",&c,&a,&b);
        if(c=='P')
            modify(a,b);
        else
            printf("%d\n",query(a,b));
    }
    return 0;
}