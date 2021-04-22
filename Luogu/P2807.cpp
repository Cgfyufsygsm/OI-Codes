#include <cstdio>

typedef long long ll;

const int maxn=505;
ll sum[maxn],f1[maxn],f2[maxn];

ll solve1(int n)
{
    if(n==1)
        return 1;
    if(n==2)
        return 4;
    if(f1[n])
        return f1[n];
    else
        return f1[n]=solve1(n-1)+sum[n];
}

ll solve2(int n)
{
    if(n<2)
        return 0;
    if(n==2)
        return 1;
    if(n==3)
        return 3;
    if(f2[n])
        return f2[n];
    else
        return f2[n]=solve2(n-2)+sum[n-1];
}

int main()
{
    for(int i=1;i<=500;i++)
        sum[i]=i+sum[i-1];
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        printf("%lld\n",solve1(n)+solve2(n));
    }
    return 0;
}