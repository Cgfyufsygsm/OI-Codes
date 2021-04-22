#include <cstdio>
#include <cctype>

typedef long long ll;
const int maxn=1e6+5;

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

ll abs(ll x)
{
    return x>=0?x:-x;
}

struct edge
{
    int to,next;
    ll w;
}e[maxn<<1];

int head[maxn],cnt;

inline void add(int u,int v,ll w)
{
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
    return;
}

int n,size[maxn];

ll dfs(int u,int fa)
{
    ll ret=0;
    size[u]=1;
    for(int i=head[u];i;i=e[i].next)
    {
        int &v=e[i].to;
        if(v==fa)
            continue;
        ll &w=e[i].w;
        ret+=dfs(v,u);
        size[u]+=size[v];
        ret+=abs(size[v]-(n-size[v]))*w;
    }
    return ret;
}

int main()
{
    n=read();
    for(int i=1;i<n;i++)
    {
        int a=read(),b=read(),c=read();
        add(a,b,c);
        add(b,a,c);
    }
    printf("%lld\n",dfs(1,0));
    return 0;
}