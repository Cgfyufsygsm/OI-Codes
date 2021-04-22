#include <cstdio>

const int maxn=105;
int a[maxn<<1],f1[maxn<<1][maxn<<1],f2[maxn<<1][maxn<<1],n,s[maxn<<1];

inline int max(int a,int b)
{
    return a>b?a:b;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        a[n+i]=a[i];
    }
    for(int i=1;i<=n<<1;i++)
        s[i]=s[i-1]+a[i];
    for(int l=1;l<n;l++)
        for(int i=1,j=i+l;j<n<<1&&i<n<<1;i++,j=i+l)
        {
            f2[i][j]=0x3f3f3f3f;
            int d=s[j]-s[i-1];
            for(int k=i;k<j;k++)
            {
                f1[i][j]=max(f1[i][j],f1[i][k]+f1[k+1][j]+d);
                f2[i][j]=min(f2[i][j],f2[i][k]+f2[k+1][j]+d);
            }
        }
    int ans1=0,ans2=0x3f3f3f3f;
    for(int i=1;i<n;i++)
    {
        ans1=max(ans1,f1[i][i+n-1]);
        ans2=min(ans2,f2[i][i+n-1]);
    }
    printf("%d\n%d\n",ans2,ans1);
    return 0;
}