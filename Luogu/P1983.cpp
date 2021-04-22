#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>

const int maxn=1000+5;
int head[maxn],to[maxn*maxn*3],next[maxn*maxn*3],e[maxn][maxn],cnt;
int n,m,tmp[1005],tmp1[1005];
int ind[maxn],dep[maxn];
std::queue<int> q;

inline int read()
{
    char c = getchar();
    int s = 0, x = 1;
    while (!isdigit(c))
    {
        if(c=='-')
            x = -x;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s*x;
}

inline int max(int a,int b)
{
    return a>b?a:b;
}

inline void add(int u,int v)
{
    to[++cnt]=v;
    next[cnt]=head[u];
    head[u]=cnt;
    return;
}

int main()
{
    n=read(),m=read();
    while(m--)
    {
        int s=read();
        memset(tmp1,0,sizeof tmp1);
        for(int i=1;i<=s;i++)
            tmp[i]=read(),tmp1[tmp[i]]=1;
        for(int i=tmp[1];i<=tmp[s];i++)
            if(!tmp1[i])
                for(int j=1;j<=s;j++)
                    if(!e[i][tmp[j]])
                        e[i][tmp[j]]=1,add(i,tmp[j]),++ind[tmp[j]];
    }
    for(int i=1;i<=n;i++)
    {
        if(!ind[i])
        {
            q.push(i);
            dep[i]=1;
        }
    }
    int ans=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=next[i])
        {
            int v=to[i];
            dep[v]=max(dep[v],dep[u]+1);
            ans=max(dep[v],ans);
            if(!--ind[v])
                q.push(v);
        }
    }
    printf("%d\n",ans);
    return 0;
}