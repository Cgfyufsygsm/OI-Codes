#include <cstdio>

typedef long long ll;
const ll mod=100003;

ll pow(ll base,ll p)
{
    base%=mod;
    ll ret=1;
    for(;p;p>>=1)
    {
        if(p&1)
            ret=ret*base%mod;
        base=base*base%mod;
    }
    return ret;
}

int main()
{
    ll n,m;
    scanf("%lld %lld",&m,&n);
    printf("%lld\n",(pow(m,n)-m*pow(m-1,n-1)%mod+mod)%mod);
    return 0;
}