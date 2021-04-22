#include <cstdio>

typedef unsigned long long ll;

ll f[1000*1000+5];

ll pow(ll base,ll p,ll mod)
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
    int t;
    scanf("%d",&t);
    while(t--)
    {
        ll a,b,n,m;
        scanf("%llu %llu %llu",&a,&b,&n);
        if(n==1 || a==0)
        {
            printf("0\n");
            continue;
        }
        if(a==1)
        {
            printf("1\n");
            continue;
        }
        f[0]=0,f[1]=f[2]=1;
        for(int i=3;;++i)
        {
            f[i]=(f[i-1]+f[i-2])%n;
            if(f[i]==1 && f[i-1]==1)
            {
                m=i-2;
                break;
            }
        }
        printf("%llu\n",f[pow(a,b,m)]);
    }
    return 0;
}