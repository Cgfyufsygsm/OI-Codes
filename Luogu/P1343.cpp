#include <cstdio>
#include <cctype>
#include <queue>
#include <cstring>

inline int read()
{
    int s=0;
    char c=getchar();
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=s*10+c-'0',c=getchar();
    return s;
}

inline int min(int a,int b){return a<b?a:b;}

const int maxn=205,maxm=2005;
int n,m,x,s,t;
int flag[maxn][maxn];
int head[maxn],to[maxm<<1],c[maxm<<1],nxt[maxm<<1],cnt=1;
int dep[maxn];

inline void add(int u,int v,int w)
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

int dfs(int u,int sum)
{
    if(u==t)
        return sum;
    int k,res=0;
    for(int i=head[u];i&&sum;i=nxt[i])
    {
        int v=to[i];
        if(c[i]>0 && dep[v]==dep[u]+1)
        {
            int k=dfs(v,min(sum,c[i]));
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
    n=t=read(),m=read(),x=read(),s=1;
    while(m--)
    {
        int a=read(),b=read(),w=read();
        if(!flag[a][b])
        {
            add(a,b,w);
            add(b,a,0);
            flag[a][b]=cnt;
        }
        else
            c[flag[a][b]^1]+=w;
    }
    int ans=0;
    while(bfs())
        ans+=dfs(1,1e9);
    if(!ans)
        printf("Orz Ni Jinan Saint Cow!\n");
    else
    {
        int pi=x/ans;
        if(ans*pi<x)
            pi++;
        printf("%d %d\n",ans,pi);
    }
    return 0;
}