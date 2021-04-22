#include <cstdio>
#include <cctype>
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

template<typename T>
inline T max(T a,T b){return a>b?a:b;}

const int maxn=1e5+5;
int p[maxn],n;
int head[maxn],to[maxn<<1],nxt[maxn<<1],cnt;
int s,t;
double k;
int f[maxn][2];

int anc[maxn];

int find(int x){return x==anc[x]?x:anc[x]=find(anc[x]);}

void uni(int a,int b){anc[find(a)]=find(b);}

bool query(int x,int y){return find(x)==find(y);}

inline void add(int u,int v)
{
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
    return;
}

void dfs(int u,int fa)
{
    f[u][1]=p[u],f[u][0]=0;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==fa)continue;
        dfs(v,u);
        f[u][0]+=max(f[v][0],f[v][1]);
        f[u][1]+=f[v][0];
    }
    return;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        p[i]=read(),anc[i]=i;
    for(int i=1;i<=n;i++)
    {
        int u=read()+1,v=read()+1;
        if(!query(u,v))
        {
            add(u,v);
            add(v,u);
            uni(u,v);
        }
        else
            s=u,t=v;
    }
    scanf("%lf",&k);
    dfs(s,0);
    double ans1=f[s][0];
    memset(f,0,sizeof f);
    dfs(t,0);
    double ans2=f[t][0];
    printf("%.1lf\n",max(ans1,ans2)*k);
    return 0;
}