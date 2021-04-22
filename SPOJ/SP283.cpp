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

inline int max(int a,int b)
{
    return a>b?a:b;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

const int maxn=3850;
int t;

int n,b,u[maxn],f[maxn][maxn][2];

void init()
{
    n=read(),b=read();
    for(int i=1;i<=n;i++)
        u[i]=read();
    return;
}

void s()
{
    int ans=0;
    memset(f,0,sizeof f);
    memset(u,0,sizeof u);
    init();
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=min(i,b);j++)
        {
            f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
            f[i][j][1]=max(f[i-1][j-1][0],j==1?0:f[i-1][j-1][1]+u[i]);
        }
    }
    ans=max(ans,max(f[n][b][0],f[n][b][1]));
    memset(f,0,sizeof f);
    f[1][1][1]=u[1];
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=min(i,b);j++)
        {
            f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
            f[i][j][1]=max(f[i-1][j-1][0],j==1?0:f[i-1][j-1][1]+u[i]);
        }
    }
    ans=max(ans,f[n][b][1]);
    printf("%d\n",ans);
}

int main()
{
    t=read();
    while(t--)
        s();
    return 0;
}