#include <cstdio>
#include <cctype>
#include <vector>

using std::vector;

const int maxn=2e4+5;
int n,m;
int dfn[maxn],low[maxn],ans,root,child,cnt;
bool cut[maxn];
vector<int> G[maxn];

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

inline int min(int a,int b)
{
    return a<b?a:b;
}

void tarjan(int u)
{
    dfn[u]=low[u]=++cnt;
    for(auto v:G[u])
    {
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u] && u!=root)
            {
                if(!cut[u])
                    ans++;
                cut[u]=1;
            }
            if(u==root)
                child++;
        }
        low[u]=min(low[u],dfn[v]);
    }
    if(u==root && child>1)
        ans++,cut[u]=1;
}

int main()
{
    n=read(),m=read();
    while(m--)
    {
        int x=read(),y=read();
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            root=i;child=0;
            tarjan(i);
        }
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
        if(cut[i])
            printf("%d ",i);
    return 0;
}