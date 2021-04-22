#include <cstdio>
#include <cctype>
#include <cstring>

typedef long long ll;
const ll maxn=1ll<<31;

int main()
{
    freopen("UVA10791.out","w",stdout);
    int kase=1;
    ll n;
    for(;scanf("%lld",&n) && n;kase++)
    {
        if(n==1)
        {
            printf("Case %d: %d\n",kase,2);
            continue;
        }
        ll ans=0,initn=n;
        int f=0;
        for(ll i=2;i*i<=n;++i)
        {
            ll tmp=1;
            if((!(n%i)) && (n!=1))
            {
                do
                {
                    tmp*=i;
                    n/=i;
                } while ((!(n%i)) && (n!=1));
                ans+=tmp;++f;
                //printf("i:%lld %lld,n:%lld\n",i,tmp,n);
            }
            if(n==1)break;
        }
        if(initn==n || (n==1&&f==1))
            ++ans;
        if(n!=1)ans+=n;
        printf("Case %d: %lld\n",kase,ans);
    }
    return 0;
}