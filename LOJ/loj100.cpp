#include <cstdio>
#include <cctype>

typedef long long ll;

const ll maxn=505,mod=1e9+7;
ll a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];

int main()
{
    int n,p,m;
    scanf("%d %d %d",&n,&p,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=p;j++)
            scanf("%lld",&a[i][j]);
    for(int i=1;i<=p;i++)
        for(int j=1;j<=m;j++)
            scanf("%lld",&b[i][j]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int k=1;k<=p;k++)
                c[i][j]=(c[i][j]+a[i][k]*b[k][j]%mod+mod)%mod;
            printf("%lld ",c[i][j]);
        }
        printf("\n");
    }
    return 0;
}