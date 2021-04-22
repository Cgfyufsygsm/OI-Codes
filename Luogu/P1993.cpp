#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>

using namespace std;

const int maxn=5e3+5;

struct edge
{
    int from,to,dist;
    edge(){}
    edge(int u,int v,int w)
    {
        from=u;
        to=v;
        dist=w;
    }
};

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

int n,m;
vector<edge> G[maxn];
int d[maxn],cnt[maxn];
bool inq[maxn];

bool spfa()
{
    memset(d,0x3f,sizeof d);
    queue<int> q;
    q.push(0),inq[0]=1,d[0]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop(),inq[u]=0;
        for(auto e:G[u])
        {
            int v=e.to,w=e.dist;
            if(d[u]+w<d[v])
            {
                d[v]=d[u]+w;
                if(!inq[v])
                {
                    if(++cnt[v]>n)
                        return false;
                    inq[v]=1;
                    q.push(v);
                }
            }
        }
    }
    return true;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        G[0].push_back(edge(0,i,0));
    while(m--)
    {
        int opt,a,b,c;
        opt=read(),a=read(),b=read(),c=opt==3?0:read();
        if(opt==1)
            G[a].push_back(edge(a,b,-c));
        else if(opt==2)
            G[b].push_back(edge(b,a,c));
        else if(opt==3)
            G[a].push_back(edge(a,b,0)),G[b].push_back(edge(b,a,0));
    }
    if(spfa())
        printf("Yes\n");
    else printf("No\n");
    return 0;
}