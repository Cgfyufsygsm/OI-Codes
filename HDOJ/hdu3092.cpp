#include <cstdio>
#include <cmath>

template<class T> T max(T a,T b)
{
    return a>b?a:b;
}

int s,m,ans[3005];
double f[3005];
int prime[500];
bool is_not_prime[3005];



int main()
{
    int cnt=0;
    for(int i=2;i<=3005;i++)
    {
        if(!is_not_prime[i])
            prime[++cnt]=i;
        for(int j=1;j<=cnt && prime[j]*i<=3005;j++)
        {
            is_not_prime[prime[j]*i]=1;
            if(i%prime[j]==0)
                break;
        }
    }
    while(scanf("%d %d",&s,&m)!=EOF)
    {
        for(int i=0;i<=s;i++)
            f[i]=0,ans[i]=1;
        for(int i=1;i<=cnt && prime[i]<=s;i++)
            for(int j=s;j>=prime[i];j--)
            {
                double tmp=log(prime[i]*1.0);
                for(int p=prime[i],q=1;p<=j;p*=prime[i],q++)
                {
                    if(f[j-p]+q*tmp>f[j])
                    {
                        f[j]=f[j-p]+q*tmp;
                        ans[j]=(ans[j-p]*p)%m;
                    }
                }
            }
        printf("%d\n",ans[s]);
    }
    return 0;
}