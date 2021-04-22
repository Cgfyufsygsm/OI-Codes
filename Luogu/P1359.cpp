#include <cstdio>

const int maxn=205;
int n,f[maxn],a[maxn][maxn];

inline int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        f[i]=0x3f3f3f3f;
        for(int j=i+1;j<=n;j++)
            scanf("%d",&a[i][j]);
    }
    f[n]=0x3f3f3f3f;
    f[1]=0;
    for(int i=2;i<=n;i++)
        for(int j=1;j<i;j++)
            f[i]=min(f[i],f[j]+a[j][i]);
    printf("%d\n",f[n]);
    return 0;
}