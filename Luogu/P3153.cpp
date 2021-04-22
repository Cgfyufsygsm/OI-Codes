#include <cstdio>
#include <cstring>
#include <queue>

int n,k;
const int maxn=1000;
int head[maxn],cur[maxn],to[maxn<<4],nxt[maxn<<4],c[maxn<<4],cnt;
int dep[maxn];
int s,t;
char tmp[55][55];

inline void add(int u,int v,int w)
{
    to[++cnt]=v;
    nxt[cnt]=head[u];
    c[cnt]=w;
    head[u]=cnt;
    return;
}

inline int min(int a,int b){return a<b?a:b;}

//男生喜欢 ：1-n 男生不喜欢 n+1-2n 女声喜欢 2n+1-3n 女生不喜欢：3n+1-4n

void build(int a)
{
    cnt=1;
    memset(head,0,sizeof head);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(tmp[i][j]=='Y')
                add(i,2*n+j,1),add(2*n+j,i,0);
            else if(tmp[i][j]=='N')
                add(n+i,3*n+j,1),add(3*n+j,n+i,0);
        }
    for(int i=1;i<=n;i++)
        add(s,i,a),add(i,s,0),
        add(i,n+i,k),add(n+i,i,0),
        add(3*n+i,2*n+i,k),add(2*n+i,3*n+i,0),
        add(2*n+i,t,a),add(t,2*n+i,0);
}

bool bfs()
{
    memset(dep,-1,sizeof dep);
    dep[s]=0;
    std::queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
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
    for(int i=head[u];i && sum;i=nxt[i])
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

int dinic()
{
    int ret=0;
    while(bfs())
        ret+=dfs(s,1e9);
    return ret;
}

int main()
{
    scanf("%d %d",&n,&k);
    s=4*n+1,t=4*n+2;
    for(int i=1;i<=n;i++)scanf("%s",tmp[i]+1);
    int ans,l=0,r=n;
    while(l<=r)
    {
        int mid=l+r>>1;
        build(mid);
        if(dinic()==mid*n)
            l=mid+1,ans=mid;
        else r=mid-1;
    }
    printf("%d\n",ans);
    return 0;
}