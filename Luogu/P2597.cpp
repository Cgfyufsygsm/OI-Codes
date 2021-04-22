#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
    {
        if(c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn=65534+5,maxm=1e6+5;

int head[maxn][3],to[maxm][3],next[maxm][3],cnt[3];
int n,ind[maxn],topo[maxn],cnttopo,lg[maxn],size[maxn];
int dep[maxn],f[maxn][18];

inline void add(int u,int v,int opt)
{
    to[++cnt[opt]][opt]=v;
    next[cnt[opt]][opt]=head[u][opt];
    head[u][opt]=cnt[opt];
    return;
}

void toposort()
{
    std::queue<int> q;
    q.push(0);
    topo[++cnttopo]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u][0];i;i=next[i][0])
        {
            int v=to[i][0];
            if(!--ind[v])
            {
                q.push(v);
                topo[++cnttopo]=v;
            }
        }
    }
    return;
}

int lca(int x,int y)
{
    if(dep[x]<dep[y])
    {
        int t=y;
        y=x;
        x=t;
    }
    while(dep[x]>dep[y])
        x=f[x][lg[dep[x]-dep[y]]-1];
    if(x==y)
        return x;
    for(int k=lg[dep[x]]-1;k>=0;k--)
        if(f[x][k]!=f[y][k])
            x=f[x][k],y=f[y][k];
    return f[x][0];
}

void dfs(int u)
{
    size[u]=1;
    for(int i=head[u][2];i;i=next[i][2])
    {
        int v=to[i][2];
        if(v==f[u][0])
            continue;
        dfs(v);
        size[u]+=size[v];
    }
    return;
}

int main()
{
    n=read();
    //0号图的边从被猎食者连向猎食者
    //1号图从猎食者连向食物
    for(int i = 1; i <= n; ++i)
        lg[i] = lg[i-1] + (1 << lg[i-1] == i);
    for(int i=1;i<=n;i++)
    {
        for(int tmp;tmp=read();)
            add(tmp,i,0),add(i,tmp,1),++ind[i];//i可以吃tmp
        if(!ind[i])
            add(0,i,0),add(i,0,1),++ind[i];
    }
    toposort();
    dep[0]=1;
    int tmp[maxn];
    memset(f,-1,sizeof f);
    for(int i=2;i<=n+1;i++)
    {
        int foods=0;
        for(int j=head[topo[i]][1];j;j=next[j][1])
            tmp[++foods]=to[j][1];
        if(foods==1)
        {
            dep[topo[i]]=dep[tmp[1]]+1;
            f[topo[i]][0]=tmp[1];
            add(topo[i],tmp[1],2);
            add(tmp[1],topo[i],2);
            for(int k=1;k<=lg[dep[topo[i]]];k++)
                f[topo[i]][k]=f[f[topo[i]][k-1]][k-1];
        }
        else
        {
            int curlca=lca(tmp[1],tmp[2]);
            for(int k=3;k<=foods;k++)
                curlca=lca(curlca,tmp[k]);
            f[topo[i]][0]=curlca;
            dep[topo[i]]=dep[curlca]+1;
            add(topo[i],curlca,2);
            add(curlca,topo[i],2);
            for(int k=1;k<=lg[dep[topo[i]]];k++)
                f[topo[i]][k]=f[f[topo[i]][k-1]][k-1];
        }
    }
    dfs(0);
    for(int i=1;i<=n;i++)
        printf("%d\n",size[i]-1);
    return 0;
}