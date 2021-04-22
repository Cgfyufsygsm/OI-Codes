#include <cstdio>
#include <cctype>

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

const int maxn=2005;
int n,H,delta,t[maxn][maxn],f[maxn][maxn],maxp[maxn];

int main()
{
    n=read(),H=read(),delta=read();
    for(int i=1;i<=n;i++)
    {
        int ni=read();
        while(ni--)
        {
            int x=read();
            t[i][x]++;
        }
    }
    for(int h=H;h>=1;h--)
        for(int i=1;i<=n;i++)
        {
            f[i][h]=max(h+delta<=H?maxp[h+delta]:f[i][h],f[i][h+1])+t[i][h];
            maxp[h]=max(maxp[h],f[i][h]);
        }
    printf("%d\n",maxp[1]);
    return 0;
}