#include <cstdio>

const int maxn=2e5+5;

int f[maxn],n,ans=-0x3f3f3f3f;

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    scanf("%d",&n);
    f[0]=0;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        f[i]=max(f[i-1]+x,x);
        ans=max(f[i],ans);
    }
    printf("%d\n",ans);
    return 0;
}