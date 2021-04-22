#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int T;
const int maxn=100000+5;

class tree
{
public:
    vector<int> g[maxn];
    bool vis[maxn];
    int depth[maxn];
    int n,d;//注意节点从0开始编号
    inline void ins(int x,int y)
    {
        g[x].push_back(y);
        g[y].push_back(x);
    }
    
    void dfs(int cur,int dep)
    {
        //printf("%d ",cur);
        depth[cur]=dep;
        for(int i=0;i<g[cur].size();i++)
            if(!vis[g[cur][i]])
            {
                vis[g[cur][i]]=1;
                dfs(g[cur][i],dep+1);
            }
        return;
    }
    int ans()
    {
        int ret=0;
        for(int i=0;i<n;i++)
            if(depth[i]>d)
                ret++;
        return ret;
    }
    void clear()
    {
        n=d=0;
        memset(depth,0,sizeof(depth));
        memset(g,0,sizeof(g));
        memset(vis,0,sizeof(vis));
        vis[0]=1;
    }
}t;

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        t.clear();
        scanf("%d %d",&t.n,&t.d);
        for(int i=1;i<t.n;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            t.ins(x,y);
        }
        t.dfs(0,0);
        printf("%d\n",t.ans());
    }
    return 0;
}