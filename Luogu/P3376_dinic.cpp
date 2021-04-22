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
int flag[maxn][maxn],dep[maxn],cur[maxn];
ll c[maxm<<1],ans;
int n,m,s,t;

inline void add(int u,int v,ll w)
{
    to[++cnt]=v;
    c[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
    return;
}

bool bfs()
{
    memset(dep,-1,sizeof dep);
    std::queue<int> q;
    q.push(s);
    dep[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(c[i]>0 && dep[v]==-1)
            {
                q.push(v);
                dep[v]=dep[u]+1;
                if(v==t)
                    return 1;
            }
        }
    }
    return 0;
}

ll dfs(int u,ll sum)
{
    if(u==t)
        return sum;
    ll k,res=0;
    for(int &i=cur[u];i && sum;i=nxt[i])
    {
        int v=to[i];
        if(c[i]>0 && (dep[v]==dep[u]+1))
        {
            k=dfs(v,min(sum,c[i]));
            if(!k)
                dep[v]=-2;
            c[i]-=k;
            c[i^1]+=k;
            res+=k;
            sum-=k;
        }
    }
    return res;
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
    {
        for(int i=1;i<=n;i++)
            cur[i]=head[i];
        ans+=dfs(s,1e18);
    }
    printf("%lld\n",ans);
    return 0;
}