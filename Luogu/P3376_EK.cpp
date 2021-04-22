#include <cstdio>
#include <cctype>
#include <queue>
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

ll min(ll a,ll b)
{
    return a<b?a:b;
}

const int maxn=205,maxm=5005;
int head[maxn],to[maxm<<1],nxt[maxm<<1],cnt=1;
int flag[maxn][maxn],vis[maxn],pre[maxn];
ll c[maxm<<1],dis[maxn];
ll ans;
int n,m,s,t;

inline void add(int u,int v,ll w)
{
    to[++cnt]=v;
    c[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
    return;
}

int bfs()
{
    memset(vis,0,sizeof vis);
    std::queue<int> q;
    q.push(s);
    vis[s]=1;
    dis[s]=1e18;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i])
        {
            if(!c[i])continue;
            int v=to[i];
            if(vis[v])continue;
            dis[v]=min(dis[u],c[i]);
            pre[v]=i;
            q.push(v);
            vis[v]=1;
            if(v==t)return 1;
        }
    }
    return 0;
}

void update()
{
    int now=t;
    while(now!=s)
    {
        int i=pre[now];
        c[i]-=dis[t];
        c[i^1]+=dis[t];
        now=to[i^1];
    }
    ans+=dis[t];
    return;
}

int main()
{
    n=read(),m=read(),s=read(),t=read();
    while(m--)
    {
        int u=read(),v=read();
        ll w=read();
        if(!flag[u][v])
        {
            add(u,v,w);
            add(v,u,0);
            flag[u][v]=cnt;
        }
        else c[flag[u][v]^1]+=w;
    }
    while(bfs())
        update();
    printf("%lld\n",ans);
    return 0;
}