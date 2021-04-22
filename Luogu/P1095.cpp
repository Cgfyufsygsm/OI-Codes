#include <cstdio>

int M,S,T,f[300005];

inline int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    scanf("%d %d %d",&M,&S,&T);
    int maxs=0;
    for(int t=1;t<=T;t++)
    {
        if(M>=10)
            f[t]=f[t-1]+60,M-=10;
        else
            f[t]=f[t-1],M+=4;
    }
    for(int t=1;t<=T;t++)
    {
        f[t]=max(f[t],f[t-1]+17),maxs=max(maxs,f[t]);
        if(f[t]>=S)
        {
            printf("Yes\n%d\n",t);
            return 0;
        }
    }
    printf("No\n%d\n",maxs);
    return 0;
}