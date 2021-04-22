#include <cstdio>

const int maxn=30000000+5;
long long f[maxn+5];

int main()
{
    int t,n;
    scanf("%d",&t);
    for(int c=1;c<=maxn;++c)
        for(int a=c<<1;a<=maxn;a+=c)
            if((a^(a-c))==c)
                ++f[a];
    for(int i=1;i<=maxn;++i)
        f[i]+=f[i-1];
    for(int kase=1;kase<=t;++kase)
    {
        scanf("%d",&n);
        printf("Case %d: %lld\n",kase,f[n]);
    }
    return 0;
}