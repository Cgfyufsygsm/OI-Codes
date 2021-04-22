#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn=500010;
int n,c[maxn],f[maxn],g[maxn],tmp[maxn];
vector<int> G[maxn];

inline void ins(int a,int b)
{
    G[a].push_back(b);
    G[b].push_back(a);
    return;
}

inline bool cmp(int x,int y)
{
    return f[x]-g[x] > f[y]-g[y];
}

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

void dfs(int now,int fa)
{
    if(now!=1)
        f[now]=c[now];
    int cnt=0;
    for(auto i:G[now])
        if(i!=fa)
            dfs(i,now);
    for(auto i:G[now])
        if(i!=fa)
            tmp[++cnt]=i;
    sort(tmp+1,tmp+cnt+1,cmp);
    for(int i=1;i<=cnt;i++)
        f[now]=max(f[now],f[tmp[i]]+g[now]+1),
        g[now]+=g[tmp[i]]+2;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        c[i]=read();
    int a,b;
    for(int i=1;i<n;i++)
    {
        a=read(),b=read();
        ins(a,b);
    }
    dfs(1,0);
    printf("%d\n",max(c[1]+g[1],f[1]));
    return 0;
}