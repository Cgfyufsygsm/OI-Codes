#include <cstdio>
#include <cctype>
#include <cstring>

typedef long long ll;

inline ll read()
{
    char c = getchar();
    ll s = 0, x = 1;
    while (!isdigit(c))
    {
        if(c=='-')
            x=-x;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s*x;
}

inline ll max(ll a,ll b)
{
    return a>b?a:b;
}

ll n,a[1005],f[1005];
const ll INF=9223372036854775807>>1;

int main()
{
    while(n=read())
    {
        for(int i=1;i<=n;i++)
            a[i]=read();
        a[0]=-INF,a[n+1]=INF;
        memset(f,-0x3f,sizeof f);
        f[0]=0;
        for(int i=1;i<=n+1;i++)
            for(int j=0;j<i;j++)
                if(a[i]>a[j])
                    f[i]=max(f[i],f[j]+(i==n+1?0:a[i]));
        printf("%lld\n",f[n+1]);
    }
    return 0;
}