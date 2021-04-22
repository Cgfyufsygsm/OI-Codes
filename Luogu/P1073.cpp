#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn=1e5+5;

struct edge
{
    int from,to,dist;
    edge(){}
    edge(int u,int v,int w)
    {
        from=u,to=v,dist=w;
    }
};

vector<edge> g[maxn*3];
queue<int> q;
bool inq[maxn*3];
int d[maxn*3];
int n,m;

void ins(int u,int v,int w)
{
    g[u].push_back(edge(u,v,w));
    return;
}

int spfa()
{
    memset(d,0x3f3f3f3f,sizeof(d));
    q.push(1);
    inq[1]=true;
    d[1]=0;
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        inq[now]=false;
        //printf("now:%d_%d\n",now%n?now%n:n,now/n);
        for(auto &e:g[now])
        {
            //printf("\tto:%d_%d\n",e.to%n?e.to%n:n,e.to/n);
            int to=e.to, dist=e.dist;
            if(d[now]+dist<d[to])
            {
                d[to]=d[now]+e.dist;
                if(!inq[to])
                {
                    inq[to]=true;
                    q.push(to);
                }
            }
        }
    }
    return d[n+(n<<1)];
}

int main()
{
    //freopen("1.out","w",stdout);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int k;
        scanf("%d",&k);
        ins(i,i+n,k);
        ins(i+n,i+(n<<1),-k);
    }
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        ins(u,v,0);
        ins(u+n,v+n,0);
        ins(u+(n<<1),v+(n<<1),0);
        if(w==2)
        {
            ins(v,u,0);
            ins(v+n,u+n,0);
            ins(v+(n<<1),u+(n<<1),0);
        }
    }
    int ans=spfa();
    printf("%d\n",ans<0?-ans:0);
    return 0;
}