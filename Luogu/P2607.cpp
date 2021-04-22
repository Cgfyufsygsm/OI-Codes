#include <cstdio>
#include <cctype>
#include <cstring>

typedef long long ll;

inline ll read()
{
    ll s=0;
    char c=getchar();
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=s*10+c-'0',c=getchar();
    return s;
}

template<typename T>
inline T max(T a,T b){return a>b?a:b;}

const int maxn=1e6+5;
ll p[maxn],f[maxn][2],ans;
int n;
int head[maxn],to[maxn],nxt[maxn],cnt;
int fa[maxn],root;
bool vis[maxn];

inline void add(int u,int v)
{
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
    return;
}

void dfs(int u)
{
    f[u][0]=0,f[u][1]=p[u];
    vis[u]=1;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==root)
            f[u][1]-=maxn;
        else
        {
            dfs(v);
            f[u][0]+=max(f[v][0],f[v][1]);
            f[u][1]+=f[v][0];
        }
    }
    return;
}

void find_circle(int u)
{
    vis[u]=1;
    root=u;
    while(!vis[fa[root]])
    {
        root=fa[root];
        vis[root]=1;
    }
    dfs(root);
    ll t=max(f[root][0],f[root][1]);
    vis[root]=1;
    root=fa[root];
    dfs(root);
    ans+=max(t,max(f[root][0],f[root][1]));
    return;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        p[i]=read();
        fa[i]=read();
        add(fa[i],i);
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])
            find_circle(i);
    printf("%lld\n",ans);
    return 0;
}