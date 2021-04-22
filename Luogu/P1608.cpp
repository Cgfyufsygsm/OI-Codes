#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#include <utility>

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

const int maxn=2005,maxm=maxn*(maxn-1);

struct edge
{
    int from,to,w,nxt;
}e[maxm];

int n,cnt,head[maxn];

inline void add(int u,int v,int w)
{
    e[++cnt].to=v;
    e[cnt].from=u;
    e[cnt].w=w;
    e[cnt].nxt=head[u];
    head[u]=cnt;
    return;
}

int mind[maxn][maxn];
int dis[maxn],f[maxn];
bool vis[maxn];

int main()
{
    memset(dis,0x3f,sizeof dis);
    memset(mind,0x3f,sizeof mind);
    n=read();
    int E=read();
    while(E--)
    {
        int i=read(),j=read(),c=read();
        if(c>=mind[i][j])
            continue;
        else add(i,j,c),mind[i][j]=c;
    }
    f[1]=1,dis[1]=0;
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
    q.push(make_pair(0,1));
    while(!q.empty())
    {
        int u=q.top().second;
        q.pop();
        if(vis[u])
            continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt)
        {
            int v=e[i].to;
            if(dis[u]+e[i].w<dis[v])
            {
                dis[v]=dis[u]+e[i].w;
                f[v]=f[u];
                q.push(make_pair(dis[v],v));
            }
            else if(dis[u]+e[i].w==dis[v])
                f[v]+=f[u];
        }
    }
    if(dis[n]>=0x3f)
        printf("No answer\n");
    else
        printf("%d %d\n",dis[n],f[n]);
    return 0;
}