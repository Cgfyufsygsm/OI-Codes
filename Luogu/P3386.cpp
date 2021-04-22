#include <cstdio>
#include <cctype>
#include <cstring>

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

const int maxn=505;
int n,m,e;
int G[maxn][maxn];
int right[maxn];
bool used[maxn];

bool find(int x)
{
    for(int j=1;j<=m;j++)
    {
        if(G[x][j] && (!used[j]))
        {
            used[j]=1;
            if((!right[j]) || find(right[j]))
            {
                right[j]=x;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    n=read(),m=read(),e=read();
    for(int i=1;i<=e;i++)
    {
        int u=read(),v=read();
        G[u][v]=1;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        memset(used,0,sizeof used);
        if(find(i))
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}