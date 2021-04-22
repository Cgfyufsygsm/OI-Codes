#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>

inline int read()
{
    int s=0;
    bool sign=0;
    char c=getchar();
    while(!isdigit(c))
        sign|=(c=='-'),c=getchar();
    while(isdigit(c))
        s=10*s+c-'0',c=getchar();
    return sign?-s:s;
}

const int maxn=5005;
int n,m;
std::vector<int> G[maxn];
std::vector<int> loop;

void dfs_tree(int u,int fa)
{
    printf("%d ",u);
    for(auto v:G[u])
        if(v!=fa)
            dfs_tree(v,u);
    return;
}

void subtask1()
{
    for(int i=1;i<=n;++i)
        std::sort(G[i].begin(),G[i].end());
    dfs_tree(1,0);
    return;
}

int dfn[maxn],cnt,s,t;
int ans[maxn],tmp[maxn];

bool find_loop(int u,int fa)
{
    if(dfn[u])
    {
        loop.push_back(u);
        s=u;
        return true;
    }
    dfn[u]=++cnt;
    for(auto v:G[u])
        if(v!=fa)
            if(find_loop(v,u))
            {
                if(u==s)
                    return false;
                loop.push_back(u);
                return true;
            }
    return false;
}

void dfs(int u,int fa)
{
    tmp[++cnt]=u;
    for(auto v:G[u])
    {
        if(v==fa || (u==s && v==t) || (u==t && v==s))
            continue;
        dfs(v,u);
    }
    return;
}

void subtask2()
{
    for(int i=1;i<=n;++i)
        std::sort(G[i].begin(),G[i].end()),ans[i]=tmp[i]=0x3f3f3f3f;
    find_loop(1,0);
    for(int i=0;i<loop.size()-1;++i)
    {
        cnt=0;
        s=loop[i],t=loop[i+1];
        dfs(1,0);
        for(int i=1;i<=n;++i)
            if(tmp[i]<ans[i])
            {
                for(int j=1;j<=n;++j)
                    ans[j]=tmp[j];
                break;
            }
            else if(tmp[i]>ans[i])
                break;
    }
    cnt=0;
    s=loop[0],t=loop[loop.size()-1];
    dfs(1,0);
    for(int i=1;i<=n;++i)
        if(tmp[i]<ans[i])
        {
            for(int j=1;j<=n;++j)
                ans[j]=tmp[j];
            break;
        }
        else if(tmp[i]>ans[i])
                break;
    for(int i=1;i<=n;++i)
        printf("%d ",ans[i]);
    return;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;++i)
    {
        int u=read(),v=read();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    if(m==n-1)
        subtask1();
    else if(m==n)
        subtask2();
    return 0;
}