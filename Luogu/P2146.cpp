#include <cstdio>
#include <cstring>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

#define db printf("debug")

const int maxn=1e5+5;

int head[maxn],to[maxn<<1],nxt[maxn<<1],cnt;

inline void add(int u,int v)
{
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
    return;
}

struct SegTree
{
    int sum;
    int tag;
    SegTree(){
        sum=0,tag=-1;
    }
}f[maxn<<2];

int n,q;
int times,dfn[maxn],son[maxn],size[maxn],fa[maxn],dep[maxn],top[maxn];

void dfs1(int u,int father,int d)
{
    fa[u]=father;
    size[u]=1;
    dep[u]=d;
    int maxson=-1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==father)
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
    dfn[u]=++times;
    top[u]=topf;
    if(son[u])
        dfs2(son[u],topf);
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa[u] || v==son[u])
            continue;
        dfs2(v,v);
    }
    return;
}

void down(int i,int j,int k)
{
    f[L].tag=f[k].tag;
    f[R].tag=f[k].tag;
    f[L].sum=(M-i+1)*f[k].tag;
    f[R].sum=(j-M)*f[k].tag;
    f[k].tag=-1;
}

int query(int i,int j,int k,int x,int y)
{
    if(x<=i && y>=j)
        return f[k].sum;
    if(f[k].tag!=-1)
        down(i,j,k);
    int ans=0;
    if(x<=M)
        ans+=query(i,M,L,x,y);
    if(y>M)
        ans+=query(M+1,j,R,x,y);
    return ans;
}

void modify(int i,int j,int k,int x,int y,int opt)
{
    if(x<=i && y>=j)
    {
        f[k].tag=opt;
        f[k].sum=(j-i+1)*opt;
        return;
    }
    if(f[k].tag!=-1)
        down(i,j,k);
    if(x<=M)
        modify(i,M,L,x,y,opt);
    if(y>M)
        modify(M+1,j,R,x,y,opt);
    f[k].sum=f[L].sum+f[R].sum;
    return;
}

inline int queryfa(int u)
{
    int v=0,ans=0;
    while(top[u]!=top[v])
    {
        ans+=query(1,n,1,dfn[top[u]],dfn[u]);
        u=fa[top[u]];
    }
    ans+=query(1,n,1,dfn[v],dfn[u]);
    return ans;
}

inline void modifyfa(int u)
{
    int v=0;
    while(top[u]!=top[v])
    {
        modify(1,n,1,dfn[top[u]],dfn[u],1);
        u=fa[top[u]];
    }
    modify(1,n,1,dfn[v],dfn[u],1);
    return;
}

inline int queryson(int u)
{
    return query(1,n,1,dfn[u],dfn[u]+size[u]-1);
}

inline void modifyson(int u)
{
    modify(1,n,1,dfn[u],dfn[u]+size[u]-1,0);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int f;
        scanf("%d",&f);
        add(i,f);
        add(f,i);
    }
    memset(fa,-1,sizeof fa);
    dfs1(0,-1,1);
    dfs2(0,0);
    scanf("%d",&q);
    char tmp[10];
    while(q--)
    {
        int idx;
        scanf("%s %d",tmp,&idx);
        if(tmp[0]=='i')
        {
            printf("%d\n",dep[idx]-queryfa(idx));
            modifyfa(idx);
        }
        else if(tmp[0]=='u')
        {
            printf("%d\n",queryson(idx));
            modifyson(idx);
        }
    }
    return 0;
}