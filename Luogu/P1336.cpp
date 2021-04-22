#include <cstdio>
#include <cctype>
#include <cstring>
typedef long long ll;

ll n,m,a[25],b[25],f[205];

inline ll read()
{
    char c = getchar();
    ll s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline ll min(ll a,ll b)
{
    return a<b?a:b;
}

inline ll ksm(ll base,ll p)
{
    ll ans=1;
    for(;p;p>>=1)
    {
        if(p&1)
            ans*=base;
        base*=base;
    }
    return ans;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
        a[i]=read(),b[i]=read();
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=n;i++)
        f[i]=a[1]*ksm(i,b[1]);
    for(int i=2;i<=m;i++)
        for(int j=n;j>=0;j--)
            for(int k=0;k<=j;k++)
                f[j]=min(f[j],f[j-k]+a[i]*ksm(k,b[i]));
    printf("%lld\n",f[n]);
    return 0;
}