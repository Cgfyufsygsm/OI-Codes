#include <cstdio>
#include <cctype>
#include <queue>

using std::vector;
using std::queue;

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

struct edge
{
    int from,to;
    int val;
    edge(){}
    edge(int u,int v,int w)
    {
        from=u;to=v;val=w;
    }
};

const int maxn=1e5+5;
int n,m,k[maxn],oud[maxn];
double f[maxn];
vector<edge> G[maxn];

inline void ins(int u,int v,int w)
{
    G[v].push_back(edge(v,u,w));
    k[u]++,oud[u]++;
}

void topo()
{
    queue<int> q;
    q.push(n);
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        for(auto e:G[now])
        {
            int to=e.to;
            f[to]+=(f[now]+e.val)/(double)k[to];
            if(!--oud[to])
                q.push(to);
        }
    }
    printf("%.2lf\n",f[1]);
}

int main()
{
    n=read(),m=read();
    while(m--)
    {
        int u=read(),v=read(),w=read();
        ins(u,v,w);
    }
    f[n]=0;
    topo();
    return 0;
}