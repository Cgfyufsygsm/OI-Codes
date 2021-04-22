#include <cstdio>
#include <cctype>
#include <cstring>

const int mod=10007;
const int maxn=100010+5;

int head[maxn],to[maxn<<1],nxt[maxn<<1],cnt;
int n;
int f[maxn][2],g[maxn][2];

template<typename T>inline T min(T a,T b){return a<b?a:b;}

inline void add(int u,int v)
{
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}

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

void dfs(int u,int fa)
{
    f[u][1]=1,f[u][0]=0;
    g[u][1]=g[u][0]=1;
    for(int i=head[u];i;i=nxt[i])
    {
        int &v=to[i];
        if(v==fa)
            continue;
        dfs(v,u);
        f[u][1]+=min(f[v][0],f[v][1]);
        if(f[v][0]==f[v][1])
            g[u][1]=g[u][1]*((g[v][0]+g[v][1])%mod)%mod;
        else
            g[u][1]=g[u][1]*g[v][f[v][0]>f[v][1]]%mod;
        f[u][0]+=f[v][1];
        g[u][0]=g[u][0]*g[v][1]%mod;
    }
    return;
}

int main()
{
    int t=read();
    while(t--)
    {
        n=read();
        cnt=0;
        memset(head,0,sizeof head);
        for(int i=1;i<n;++i)
        {
            int u=read(),v=read();
            add(u,v);
            add(v,u);
        }
        dfs(1,0);
        int ans1=min(f[1][0],f[1][1]);
        int ans2;
        if(f[1][0]==f[1][1])
            ans2=(g[1][0]+g[1][1])%mod;
        else ans2=g[1][f[1][0]>f[1][1]];
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}