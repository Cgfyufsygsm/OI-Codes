#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

const int maxn=1e4+5;
const int inf= +0x7fffffff;

struct edge
{
    int to,dist;
    edge(){}
    edge(int b,int c)
    {
        to=b,dist=c;
    }
};

bool operator>(const edge &a,const edge &b)
{
    return a.dist<b.dist;
}

int n,m,s;
vector<edge> g[maxn];
priority_queue<pair<int,int>, vector<pair<int,int> >,greater<pair<int,int> > > q;
bool vis[maxn];
int d[maxn];

void ins(int u,int v,int w)
{
    g[u].push_back(edge(v,w));
    return;
}

void dijkstra()
{
    memset(d,0x3f3f3f3f,sizeof(d));
    d[s]=0;
    q.push(make_pair(0,s));
    while (!q.empty())
    {
        int now=q.top().second;
        q.pop();
        if(!vis[now])
        {
            //printf("now:%d\n",now);
            vis[now]=1;
            for(auto &e:g[now])
            {
                //printf("\tto:%d\n",e.to);
                if(d[e.to]>d[now]+e.dist)
                {
                    //printf("dayu\n");
                    d[e.to]=d[now]+e.dist;
                    q.push(make_pair(d[e.to],e.to));
                }
            }
        }
    }
    return;
}

int main()
{
    scanf("%d %d %d",&n,&m,&s);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        ins(u,v,w);
    }
    dijkstra();
    for(int i=1;i<=n;i++)
        printf("%d ",d[i]==0x3f3f3f3f?inf:d[i]);
    return 0;
}