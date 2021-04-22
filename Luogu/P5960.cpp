#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>

using namespace std;

const int maxn=5e3+5;

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

struct edge
{
    int u,v,w;
    edge(){}
    edge(int from,int to,int dist)
    {
        u=from,v=to,w=dist;
    }
};

int n,m;
vector<edge> G[maxn];

int dis[maxn],cnt[maxn];
bool inq[maxn];

int main()
{
    n=read(),m=read();
    while (m--)
    {
        int i=read(),j=read(),k=read();
        G[j].push_back(edge(j,i,k));
    }
    for(int i=1;i<=n;i++)
        G[0].push_back(edge(0,i,0));
    memset(dis,0x3f,sizeof dis);
    queue<int> q;
    q.push(0);
    dis[0]=0;inq[0]=1;cnt[0]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        inq[u]=0;
        for(auto e:G[u])
        {
            int v=e.v,w=e.w;
            if(dis[u]+w<dis[v])
            {
                dis[v]=dis[u]+w;
                if(!inq[v])
                {
                    if(++cnt[v]>=n)
                    {
                        printf("NO\n");
                        return 0;
                    }
                    inq[v]=1;
                    q.push(v);
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
        printf("%d ",dis[i]);
    return 0;
}