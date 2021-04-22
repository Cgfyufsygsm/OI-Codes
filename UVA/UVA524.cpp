#include <cstdio>

int n,a[17];
bool vis[17],is_prime[17<<1];

void dfs(int cur)
{
    if(cur==n+1 && is_prime[a[1]+a[n]])
    {
        for(int i=1;i<n;i++)
            printf("%d ",a[i]);
        printf("%d\n",a[n]);
        return;
    }
    for(int i=2;i<=n;i++)
    {
        if(is_prime[a[cur-1]+i] && !vis[i])
        {
            a[cur]=i;
            vis[i]=1;
            dfs(cur+1);
            vis[i]=0;
        }
    }
}

void make_prime()
{
    for(int i=1;i<=17<<1;++i)
        is_prime[i]=1;
    for(int i=2;i<=17;i++)
        for(int j=2;j*i<=34;j++)
            is_prime[i*j]=0;
    return;
}

int main()
{
    int kase=0;
    make_prime();
    a[1]=1;
    while(scanf("%d",&n)!=EOF)
    {
        if(kase++)
            printf("\n");
        printf("Case %d:\n",kase);
        dfs(2);
    }
    return 0;
}