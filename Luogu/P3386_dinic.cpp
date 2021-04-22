#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>

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

int n,left,m;
int s,t;
const int maxn=1010,maxm=5e4+5;
int head[maxn],to[maxm<<1],nxt[maxm<<1],c[maxm<<1],cnt=1;
bool flag[maxn][maxn];
int dep[maxn],cur[maxn];

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
    std::queue<int> q;
    memset(dep,-1,sizeof dep);
    dep[s]=0;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(c[i]>0 && dep[v]==-1)
            {
                dep[v]=dep[u]+1;
                q.push(v);
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
    left=read(),n=left+read(),m=read();
    while(m--)
    {
        int u=read(),v=read()+left;
        if(!flag[u][v])
        {
            add(u,v,1);
            add(v,u,0);
            flag[u][v]=1;
        }
    }
    s=n+1,t=n+2;
    for(int i=1;i<=left;i++)
        add(s,i,1),add(i,s,0);
    for(int i=left+1;i<=n;i++)
        add(i,t,1),add(t,i,0);
    int ans=0;
    while(bfs())
    {
        for(int i=1;i<=n+2;i++)
            cur[i]=head[i];
        ans+=dfs(s,1000);
    }
    printf("%d\n",ans);
}