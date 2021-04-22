#include <cstdio>
#include <cctype>

const int maxn=505;
int a[maxn],n,m,mod,b;
int f[maxn][maxn];

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

int main()
{
    n=read(),m=read(),b=read(),mod=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    f[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=a[i];k<=b;k++)
                f[j][k]=(f[j][k]+f[j-1][k-a[i]])%mod;
    int ans=0;
    for(int i=0;i<=b;i++)
        ans=(ans+f[m][i])%mod;
    printf("%d\n",ans);
    return 0;
}