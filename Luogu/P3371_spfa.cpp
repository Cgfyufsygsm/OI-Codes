#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
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

int n,m,s;
vector<edge> g[maxn];
queue<int> q;
bool inq[maxn];
int d[maxn];

void ins(int u,int v,int w)
{
    g[u].push_back(edge(v,w));
    return;
}

void spfa()
{
    memset(d,0x3f3f3f3f,sizeof(d));
    q.push(s);
    inq[s]=1;
    d[s]=0;
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        inq[now]=0;
        for(auto &i:g[now])
        {
            int to=i.to,dist=i.dist;
            if(d[now]+dist<d[to])
            {
                d[to]=d[now]+dist;
                if(!inq[to])
                {
                    inq[to]=1;
                    q.push(to);
                }
            }
        }
    }
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
    spfa();
    for(int i=1;i<=n;i++)
        printf("%d ",d[i]==0x3f3f3f3f?inf:d[i]);
    return 0;
}