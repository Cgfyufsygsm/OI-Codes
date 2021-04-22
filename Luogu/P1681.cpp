#include <cstdio>

inline int min(int a,int b)
{
    return a<b?a:b;
}

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=1505;
int n,m,ans,a[maxn][maxn],f[maxn][maxn];

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            f[i][j]=1;
            scanf("%d",&a[i][j]);
            if(a[i][j]!=a[i-1][j] && a[i][j]!=a[i][j-1])
                f[i][j]=min(min(f[i-1][j-1],f[i-1][j]),f[i][j-1])+1;
            ans=max(f[i][j],ans);
        }
    printf("%d\n",ans);
    return 0;
}