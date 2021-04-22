#include <utility>
#include <cstdio>
#include <cctype>
#include <queue>

using std::priority_queue;
using std::make_pair;
using std::vector;
using std::pair;

const int maxn=1e5+5;
int n,money[maxn],stop[maxn];
int f[maxn][2];

vector<int> g[maxn];

inline void ins(int from,int to)
{
    g[from].push_back(to);
    g[to].push_back(from);
    return;
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
    if(g[now].size()==1)
    {
        f[now][0]=money[now];
        return;
    }
    priority_queue<pair<int,int> > q;
    for(int i=0;i<g[now].size();i++)
    {
        if(g[now][i]!=fa)
        {
            dfs(g[now][i],now);
            q.push(make_pair(f[g[now][i]][0],g[now][i]));
        }
    }
    int lastChosen;
    for(int i=1; (!q.empty()) && (now==1 ? 1 : i<stop[now]);i++)
    {
        int to=q.top().second,val=q.top().first;
        if(val<0)
            break;
        if(val==0)
            f[now][1]=1;
        f[now][0] += val;
        lastChosen=val;
        f[now][1] |= f[to][1];
        q.pop();
    }
    f[now][0]+=money[now];
    if(q.size() && q.top().first==lastChosen)
        f[now][1]=1;
    return;
}

int main()
{
    n=read();
    for(int i=1;i<n;i++)
        money[i+1]=read();
    for(int i=1;i<n;i++)
        stop[i+1]=read();
    int from,to;
    for(int i=1;i<n;i++)
    {
        from=read(),to=read();
        ins(from,to);
    }
    dfs(1,0);
    printf("%d\n",f[1][0]);
    if(f[1][1])
        printf("solution is not unique\n");
    else
        printf("solution is unique\n");
    return 0;
}