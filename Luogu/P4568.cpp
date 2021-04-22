#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn=1e4+5;

struct edge
{
    int to,dist;
    edge(){}
    edge(int b,int c)
    {
        to=b,dist=c;
    }
};

vector<edge> g[maxn*11];
int n,m,k,s,t;
queue<int> q;
bool vis[maxn*11];
int d[maxn*11];

void ins(int u,int v,int w)
{
    g[u].push_back(edge(v,w));
    return;
}

void dij()
{
    priority_queue<pair<int,int>, vector<pair<int,int> >,greater<pair<int,int> > > q;
    memset(d,0x3f3f3f3f,sizeof(d));
    d[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
    {
        int now=q.top().second;
        q.pop();
        if(!vis[now])
        {
            vis[now]=1;
            for(auto &e:g[now])
            {
                if(d[e.to]>d[now]+e.dist)
                {
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
    scanf("%d %d %d",&n,&m,&k);
    scanf("%d %d",&s,&t);
    register int a,b,c;
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d %d",&a,&b,&c);
        for(int j=0;j<=k;j++)
        {
            ins(a+n*j,b+n*j,c);
            ins(b+n*j,a+n*j,c);
            if(j<k)
            {
                ins(a+n*j,b+(j+1)*n,0);
                ins(b+n*j,a+(j+1)*n,0);
            }
        }
    }
    dij();
    int ans=0x3f3f3f3f;
    for(int i=0;i<=k;i++)
        ans=min(ans,d[i*n+t]);
    printf("%d\n",ans);
    return 0;
}