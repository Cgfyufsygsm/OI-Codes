#include <cstdio>

int n,k;
const int p=1e9+7,maxn=2e3+5;
int f[maxn][maxn];

int main()
{
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++)
        f[1][i]=1;
    for(int i=1;i<k;i++)
        for(int j=1;j<=n;j++)
            for(int kk=1;kk*j<=n;kk++)
                f[i+1][kk*j]=(f[i+1][kk*j]+f[i][j])%p;
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=(ans+f[k][i])%p;
    printf("%d\n",ans);
}