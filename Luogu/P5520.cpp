#include <cstdio>

typedef long long ll;

int main()
{
    ll t,n,m,p;
    scanf("%lld %lld %lld %lld",&t,&n,&m,&p);
    ll ans=1;
    for(int i=n-2*m+2;i<=n-m+1;++i)
        ans=ans*i%p;
    printf("%lld\n",ans);
    return 0;
}
