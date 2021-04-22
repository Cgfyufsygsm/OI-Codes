#include <cstdio>
#include <cmath>
typedef unsigned long long ll;

ll gcd(ll x, ll y)
{
    ll tag=1;
    while(x!=y)
    {
        if(x&1==0 && y&1==0)
            x>>1,y>>1,tag<<1;
        else if(x&1==0)
            x>>1;
        else if(y&1==0)
            y>>1;
        else
        {
            if(x<y)
                x^=y^=x^=y;
            x=x-y;
        }
    }
    return x;
}

int main()
{
    ll x0,y0;
    scanf("%llu %llu",&x0,&y0);
    ll prod=x0*y0,ans=0;
    for(ll i=x0;i<=y0;i++)
    {
        if(!(prod%i))
        {
            ll gcdcur=gcd(i,prod/i);
            if(gcdcur==x0 && prod/gcdcur==y0)
                ans++;//printf("%d %d gcd:%d lcm%d\n",i,prod/i,gcdcur,prod/gcdcur);
        }
    }
    printf("%llu\n",ans);
    return 0;
}