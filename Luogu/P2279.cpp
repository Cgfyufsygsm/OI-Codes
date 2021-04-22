#include <cstdio>
#include <cctype>
#include <cstring>

const int maxn=1005;
int head[maxn],to[maxn<<1],nxt[maxn<<1],cnt;
int n;

inline void add(int u,int v)
{
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
    return;
}

inline int min(int a,int b)
{
    return a<b?a:b;
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

int f[maxn][5];

void dfs(int u,int fa)
{
    f[u][0]=1;
    f[u][3]=f[u][4]=0;
    int sum2=0,sum3=0;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa)
            continue;
        dfs(v,u);
        f[u][0]+=f[v][4];
        f[u][3]+=f[v][2];
        f[u][4]+=f[v][3];
        sum2+=f[v][2];
        sum3+=f[v][3];
    }
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa)
            continue;
        f[u][2]=min(f[u][2],sum2-f[v][2]+f[v][1]);
        f[u][1]=min(f[u][1],sum3-f[v][3]+f[v][0]);
    }
    f[u][1]=min(f[u][1],f[u][0]);
    f[u][2]=min(f[u][2],f[u][1]);
    f[u][3]=min(f[u][3],f[u][2]);
    f[u][4]=min(f[u][4],f[u][3]);
    return;
}

int main()
{
    n=read();
    for(int i=2;i<=n;i++)
    {
        int j=read();
        add(i,j);
        add(j,i);
    }
    memset(f,0x3f,sizeof f);
    dfs(1,0);
    printf("%d\n",f[1][2]);
    return 0;
}