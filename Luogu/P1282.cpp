#include <cstdio>

inline int min(int a,int b)
{
    return a<b?a:b;
}

inline int abs(int x)
{
    return x>=0?x:-x;
}

const int maxn=1005,inf=0x3f3f3f3f;
int a[maxn],b[maxn],n,sum,f[maxn][6*maxn];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",a+i,b+i);
        sum+=a[i]+b[i];
        for(int j=0;j<=6*n;j++)
            f[i][j]=inf;
    }
    f[1][b[1]]=1,f[1][a[1]]=0;
    for(int i=2;i<=n;i++)
        for(int j=0;j<=6*n;j++)
        {
            if(j-a[i]>=0)
                f[i][j]=min(f[i][j],f[i-1][j-a[i]]);
            if(j-b[i]>=0)
                f[i][j]=min(f[i][j],f[i-1][j-b[i]]+1);
        }
    int mind=inf,ans=inf;
    for(int i=1;i<=sum;i++)
    {
        if(f[n][i]<inf)
        {
            if(abs(i-(sum-i))<mind)
                mind=abs(i-(sum-i)),ans=f[n][i];
            else if(abs(i-(sum-i))==mind)
                ans=min(ans,f[n][i]);
        }
    }
    printf("%d\n",ans);
    return 0;
}