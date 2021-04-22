#include <cstdio>
#include <cctype>
#include <queue>

using namespace std;

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
    int from,to,val;
    edge(){}
    edge(int u,int v,int w)
    {
        from=u,to=v,val=w;
    }
};

struct node
{
    int now;
    int used;
    node(){}
    node(int a,int b){now=a,used=b;}
};

int n,a,b;
bool vis[105];
vector<edge> G[105];

int bfs()
{
    deque<node> q;
    q.push_back(node(a,0));
    while(!q.empty())
    {
        node now=q.front();
        q.pop_front();
        if(vis[now.now])
            continue;
        vis[now.now]=1;
        if(now.now==b)
            return now.used;
        for(auto e:G[now.now])
        {
            if(e.val==0)
                q.push_front(node(e.to,now.used));
            else
                q.push_back(node(e.to,now.used+1));
        }
    }
    return -1;
}

int main()
{
    n=read(),a=read(),b=read();
    int k,to;
    for(int i=1;i<=n;i++)
    {
        k=read();
        for(int j=1;j<=k;j++)
        {
            to=read();
            G[i].push_back(edge(i,to,j==1?0:1));
        }
    }
    printf("%d\n",bfs());
    return 0;
}