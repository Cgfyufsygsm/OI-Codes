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

inline int abs(int x)
{
    return x<0?-x:x;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

const int maxn=105;
int n,e,m[maxn];
int f[maxn][maxn],g[maxn][maxn];

int main()
{
    n=read(),e=read();
    for(int i=1;i<=n;i++)
        m[i]=read();
    for(int i=0;i<=n+1;i++)
        for(int j=i+1;j<=n+1;j++)
            for(int k=i+1;k<=j-1;k++)
                if(i==0)
                    g[i][j]+=abs(2*(m[j]-m[k]));
                else if(j==n+1)
                    g[i][j]+=abs(2*(m[i]-m[k]));
                else
                    g[i][j]+=abs(2*m[k]-m[i]-m[j]);
    memset(f,0x3f,sizeof f);
    f[0][0]=0;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            if(f[i][j]<=e)
                for(int k=i+1;k<=n+1;k++)
                    f[k][j+1]=min(f[k][j+1],f[i][j]+g[i][k]);
    for(int i=2;i<=n+1;i++)
        if(f[n+1][i]<=e)
        {
            printf("%d %d\n",i-1,f[n+1][i]);
            return 0;
        }

}