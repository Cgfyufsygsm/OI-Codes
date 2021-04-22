#include <cstdio>

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=205;
int n,f[maxn][maxn],a[maxn];

//f[i][j]表示[i,j]区间内的珠合并后能达到的最大价值

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        a[n+i]=a[i];
    }
    int ans=0;
    for(int l=2;l<=n;l++)
        for(int i=1,j=i+l-1;i<n<<1&&j<=n<<1;i++,j++)
            for(int k=i;k<j;k++)
            {
                f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]+a[i]*a[k+1]*a[j+1]);
                ans=max(ans,f[i][j]);
            }
    printf("%d\n",ans);
    return 0;
}