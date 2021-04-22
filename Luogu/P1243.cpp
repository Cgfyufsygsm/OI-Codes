#include <cstdio>

int n2[32],a[32];
int n,k,cnt1;

bool dfs(int head,int k)
{
    a[++cnt1]=head;
    if(k==1)
    {
        for(int i=1;i<=cnt1;i++)
            printf("%d ",a[i]);
        return true;
    }
    k--,head++;
    for(int i=n-head;k>n2[i] && i>=0;k-=n2[i],i--,head++);
    if(dfs(head,k))
        return true;
    cnt1--;
    return false;
}

int main()
{
    scanf("%d %d",&n,&k);
    if(k==1)
    {
        printf("0");
        return 0;
    }
    n2[0]=1;
    for(int i=1;i<=31;i++)
        n2[i]=n2[i-1]<<1;
    int head=1;
    k--;
    for(int i=n-1;k>n2[i];k-=n2[i],head++,i--);
    dfs(head,k);
    return 0;
}