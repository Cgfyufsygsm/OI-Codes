#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
using namespace std;

const int maxn=100000+5;
vector<int> g[maxn];
int n,m,ind[maxn],f[maxn],ans;

inline int read()
{
    int s=0;
    char c=getchar();
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=10*s+c-'0',c=getchar();
    return s;
}

void topo()
{
    queue<int> q;
    for(int i=1;i<=n;i++)
        if(!ind[i] && g[i].size())
            q.push(i),f[i]=1;
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        if(g[now].size()==0)
        {
            ans+=f[now];
            continue;
        }
        for(auto to:g[now])
        {
            f[to]+=f[now];
            ind[to]--;
            if(!ind[to])
                q.push(to);
        }
    }
    return;
}

int main()
{
    n=read(),m=read();
    int a,b;
    for(int i=1;i<=m;i++)
    {
        a=read(),b=read();
        ind[b]++;
        g[a].push_back(b);
    }
    topo();
    printf("%d\n",ans);
    return 0;
}