#include <cstdio>

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=1e4+5;
int n,a[maxn],b[maxn],f[maxn][maxn];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;++i)
        scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(a[i]==b[j])
                f[i][j]=max(f[i][j],f[i-1][j-1]+1);
            else
                f[i][j]=max(f[i-1][j],f[i][j-1]);
        }
    printf("%d\n",f[n][n]);
    return 0;
}