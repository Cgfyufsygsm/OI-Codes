#include <cstdio>
#include <cctype>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

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

inline void swap(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
}

typedef long long ll;
const ll maxn=300000+5,mod=998244353;

ll f[maxn<<2][52];
int dfn[maxn],top[maxn],size[maxn],son[maxn],fa[maxn],dep[maxn],dept[maxn],times;
int n,m;

int head[maxn],to[maxn<<1],next[maxn<<1],cnt;

inline void add(int u,int v)
{
    to[++cnt]=v;
    next[cnt]=head[u];
    head[u]=cnt;
}

void dfs1(int u,int father,int d)
{
    size[u]=1;
    dep[u]=d;
    fa[u]=father;
    int maxson=-1;
    for(int i=head[u];i;i=next[i])
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
    dept[dfn[u]]=dep[u];
    top[u]=topf;
    if(son[u])
        dfs2(son[u],topf);
    for(int i=head[u];i;i=next[i])
    {
        int v=to[i];
        if(v==fa[u] || v==son[u])
            continue;
        dfs2(v,v);
    }
    return;
}

void build(int i,int j,int k)
{
    if(i==j)
    {
        f[k][0]=1;
        for(int p=1;p<=50;p++)
            f[k][p]=f[k][p-1]*dept[i]%mod;
        return;
    }
    build(i,M,L);
    build(M+1,j,R);
    for(int p=1;p<=50;p++)
        f[k][p]=(f[L][p]+f[R][p])%mod;
    return;
}

ll query(int i,int j,int k,int x,int y,int p)
{
    if(x>y)
        return 0;
    if(x<=i && y>=j)
        return f[k][p];
    ll ret=0;
    if(x<=M)
        ret=(ret+query(i,M,L,x,y,p))%mod;
    if(y>M)
        ret=(ret+query(M+1,j,R,x,y,p))%mod;
    return ret;
}

int query(int u,int v,int p)
{
    int ans=0;
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]])
            swap(u,v);
        ans+=query(1,n,1,dfn[top[u]],dfn[u],p);
        ans%=mod;
        u=fa[top[u]];
    }
    if(dep[u]>dep[v])
        swap(u,v);
    ans+=query(1,n,1,dfn[u],dfn[v],p);
    ans%=mod;
    return ans;
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
    dfs1(1,0,0);
    dfs2(1,1);
    build(1,n,1);
    m=read();
    while(m--)
    {
        int i=read(),j=read(),k=read();
        printf("%d\n",query(i,j,k));
    }
    return 0;
}