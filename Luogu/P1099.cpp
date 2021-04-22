#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>

using std::vector;

const int maxn=500000+5;

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

template<typename T> inline T max(T a,T b){return a>b?a:b;}
template<typename T> inline T min(T a,T b){return a<b?a:b;}

int n,s;

struct edge
{
    int from,to,w,nxt;
}e[maxn<<1];

int head[maxn],cntedge;

inline void add(int u,int v,int w)
{
    e[++cntedge].to=v;
    e[cntedge].w=w;
    e[cntedge].from=u;
    e[cntedge].nxt=head[u];
    head[u]=cntedge;
    return;
}

int dis[maxn];
int disp1[maxn],disp2[maxn];
int p1,p2;//直径的两个端点
bool vis[maxn];
vector<int> diam;

void dfs1(int u,int fa)
{
    for(int i=head[u];i;i=e[i].nxt)
    {
        int &v=e[i].to;
        if(v==fa)
            continue;
        dis[v]=dis[u]+e[i].w;
        dfs1(v,u);
    }
    return;
}

bool find_diameter(int u,int fa)
{
    if(u==p2)
        return true;
    for(int i=head[u];i;i=e[i].nxt)
    {
        int &v=e[i].to;
        if(v==fa)continue;
        disp1[v]=disp1[u]+e[i].w;
        if(find_diameter(v,u))
        {
            diam.push_back(v);
            return true;
        }
    }
    return false;
}

int dfs2(int u)
{
    vis[u]=1;
    int tmp=0;
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(vis[v])continue;
        dis[v]=dis[u]+e[i].w;
        dfs2(v);
        tmp=max(tmp,dis[v]);
    }
    return tmp;
}

int main()
{
    n=read(),s=read();
    for(int i=1;i<n;++i)
    {
        int u=read(),v=read(),w=read();
        add(u,v,w);
        add(v,u,w);
    }
    dfs1(1,0);
    for(int i=1,maxdist=0;i<=n;dis[i++]=0)
        if(dis[i]>maxdist)
            maxdist=dis[i],p1=i;
    dfs1(p1,0);
    for(int i=1,maxdist=0;i<=n;dis[i++]=0)
        if(dis[i]>maxdist)
            maxdist=dis[i],p2=i;
    find_diameter(p1,0);
    diam.push_back(p1);
    for(int i:diam)
        vis[i]=true;
    for(int i=1;i<=n;++i)
        disp2[i]=disp1[p2]-disp1[i];
    for(int i=1;i<=n;++i)
        dis[i]=dfs2(i);
    int ans=0x3f3f3f3f;
    for(int i=0;i<diam.size();++i)
    {
        int tmp=0;
        for(int j=i;j<diam.size();++j)
        {
            if(disp1[diam[i]]-disp1[diam[j]]>s)break;
            tmp=max(tmp,dis[diam[j]]);
            int tmp1=max(tmp,max(disp1[diam[j]],disp2[diam[i]]));
            ans=min(ans,tmp1);
        }
    }
    printf("%d\n",ans);
    return 0;
}