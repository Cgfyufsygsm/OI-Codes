#include <cstdio>
#include <cctype>
#include <queue>
#include <cstring>

using namespace std;

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

const int maxn=2e3+5;

struct edge
{
    int u,v,w;
    edge(){}
    edge(int from,int to,int cost)
    {
        u=from,v=to,w=cost;
    }
};

class solve
{
private:
    int n,m;
    int dis[maxn],cnt[maxn];
    bool inq[maxn];
    vector<edge> G[maxn];
    queue<int> q;
    void clear()
    {
        for(int i=1;i<=n;i++)
            G[i].clear();
        while(q.size())
            q.pop();
        memset(dis,0x3f,sizeof dis);
        memset(inq,0,sizeof inq);
        memset(cnt,0,sizeof cnt);
        return;
    }
public:
    void init()
    {
        n=read(),m=read();
        clear();
        while(m--)
        {
            int u=read(),v=read(),w=read();
            if(w>=0)
            {
                G[u].push_back(edge(u,v,w));
                G[v].push_back(edge(v,u,w));
            }
            else
                G[u].push_back(edge(u,v,w));
        }
        return;
    }
    void spfa()
    {
        dis[1]=0;
        inq[1]=1;
        cnt[1]=1;
        q.push(1);
        while(!q.empty())
        {
            int now=q.front();
            q.pop();
            inq[now]=0;
            for(auto e:G[now])
            {
                int to=e.v,w=e.w;
                if(dis[now]+w<dis[to])
                {
                    dis[to]=dis[now]+w;
                    if(!inq[to])
                    {
                        if(++cnt[to]>n)
                        {
                            printf("YES\n");
                            return;
                        }
                        inq[to]=1;
                        q.push(to);
                    }
                }
            }
        }
        printf("NO\n");
        return;
    }
}s;

int main()
{
    int t=read();
    while(t--)
    {
        s.init();
        s.spfa();
    }
    return 0;
}