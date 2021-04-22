#include <cstdio>
#include <cctype>
#include <cstring>

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

const int maxn=105;
int G[maxn][maxn];
int n,m;

int used[maxn],match[maxn],match1[maxn];

bool find(int i)
{
    for(int j=m+1;j<=n;j++)
    {
        if(G[i][j] && (!used[j]))
        {
            used[j]=1;
            if(!match[j] || find(match[j]))
            {
                match[j]=i;
                match1[i]=j;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    m=read(),n=read();
    int u=read(),v=read();
    while(u>0 && v>0)
    {
        G[u][v]=1;
        u=read(),v=read();
    }
    int ans=0;
    for(int i=1;i<=m;i++)
    {
        memset(used,0,sizeof used);
        if(find(i))
            ans++;
    }
    printf("%d\n",ans);
    for(int i=1;i<=m;i++)
        if(match1[i])
            printf("%d %d\n",i,match1[i]);
    return 0;
}