#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct Edge
{
    int from,to,dist;
};

const int maxn=106;
vector<Edge> g[maxn];
int n,p,c[maxn],ind[maxn],oud[maxn];
queue<int> q;

void ins(int u,int v,int w)
{
    g[u].push_back((Edge){u,v,w});
    return;
}

void topo()
{
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        for(auto &i:g[now])
        {
            int to=i.to;
            if(c[now]>0)
                c[to]+=c[now]*i.dist;
            if(!--ind[to])
                q.push(to);
        }
    }
    return;
}

int main()
{
    scanf("%d %d",&n,&p);
    for(int i=1;i<=n;i++)
    {
        int u;
        scanf("%d %d",&c[i],&u);
        if(c[i])
            q.push(i);
        else
            c[i]-=u;
    }
    for(int i=1;i<=p;i++)
    {
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        ins(u,v,w);
        ind[v]++,oud[u]++;
    }
    topo();
    bool flag=0;
    for(int i=1;i<=n;i++)
    {
        if(c[i]>0 && oud[i]==0)
        {
            printf("%d %d\n",i,c[i]);
            flag=1;
        }
    }
    if(!flag)
        printf("NULL\n");
    return 0;
}