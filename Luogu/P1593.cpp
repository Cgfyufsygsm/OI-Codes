#include <cstdio>
#include <vector>

const int mod=9901,maxn=5e7+10;

int pow(int base,int p)
{
    int ret=1;
    base%=mod;
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
    int a,b;
    scanf("%d %d",&a,&b);
    if(b==0)
    {
        printf("1\n");
        return 0;
    }
    int ans=1,cnt=0;
    for(int i=2;i*i<=a;++i)
    {
        int t=0;
        if((!(a%i))&&a!=1)
        {
            do
            {
                t++;
                a/=i;
            }while((!(a%i))&&a!=1);
        }
        t*=b;
        if(i%mod==1)
            ans=ans*(t+1)%mod;
        else
        {
            ans=ans*(pow(i,t+1)+mod-1)%mod;
            ans=ans*(pow(i-1,mod-2)+mod)%mod;
        }
        if(a==1)break;
    }
    if(a!=1)
    {
        if(a%mod==1)
            ans=ans*(b+1)%mod;
        else
        {
            ans=ans*(pow(a,b+1)+mod-1)%mod;
            ans=ans*(pow(a-1,mod-2)+mod)%mod;
        }
    }
    printf("%d\n",ans%mod);
    return 0;
}