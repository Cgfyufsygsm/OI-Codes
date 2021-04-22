#include <cstdio>
#include <cstring>

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=125;
int n,s[maxn][maxn],a[maxn][maxn],f[maxn],tmp[maxn];

int getsum()
{
    memset(f,0,sizeof(f));
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        f[i]=max(f[i-1]+tmp[i],f[i]);
        ans=max(ans,f[i]);
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&a[i][j]);
            s[i][j]+=s[i-1][j]+a[i][j];
        }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
        {
            for(int k=1;k<=n;k++)
                tmp[k]=s[j][k]-s[i-1][k];
            ans=max(ans,getsum());
        }
    printf("%d\n",ans);
    return 0;
}