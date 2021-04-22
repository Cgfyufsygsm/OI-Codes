#include <cstdio>
typedef long long ll;

const int maxn=1e3+5;
ll n,x,lose[maxn],win[maxn],use[maxn],f[maxn];

inline ll max(ll a,ll b)
{
    return a>b?a:b;
}

int main()
{
    scanf("%lld %lld",&n,&x);
    ll ans=0;
    for(int i=1;i<=n;i++)
        scanf("%lld %lld %lld",lose+i,win+i,use+i);
    for(int i=1;i<=n;i++)
        for(int j=x;j>=0;j--)
        {
            if(j<use[i])
                f[j]+=lose[i];
            else
                f[j]=max(f[j]+lose[i],f[j-use[i]]+win[i]);
            ans=max(ans,f[j]);
        }
    printf("%lld\n",ans*5);
    return 0;
}