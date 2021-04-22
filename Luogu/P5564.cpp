#include <cstdio>
#include <cctype>
#include <cstring>
#define f(i,j) f[i][j+maxn]

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

typedef long long ll;
const int maxn=100+5,maxm=2000+5;
const int mod=998244353;

int n,m;
ll a[maxn][maxm],s[maxn];//n 方法，m食材
ll ans=1;
ll f[maxn][maxn<<1];

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
            a[i][j]=read(),s[i]=(s[i]+a[i][j])%mod;
        ans=ans*(s[i]+1)%mod;
    }
    ans=(ans-1ll)%mod;
    for(int gg=1;gg<=m;++gg)
    {
        memset(f,0,sizeof f);
        f(0,0)=1;
        for(int i=1;i<=n;++i)
            for(int j=-i;j<=i;++j)
                f(i,j)=(f(i-1,j)+f(i-1,j-1)*a[i][gg]+f(i-1,j+1)*(s[i]-a[i][gg]))%mod;
        for(int j=1;j<=n;++j)
            ans=(ans-f(n,j)+mod)%mod;
    }
    printf("%lld\n",ans);
    return 0;
}