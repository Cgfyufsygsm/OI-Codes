#include <cstdio>

const int maxn=1e5+5;
int n,m,a[maxn],sum[maxn];

bool check(int mid)
{
    int cnt=0,lastans=1;
    for(int i=1;i<=n;i++)
    {
        if(sum[i]-sum[lastans-1]>mid)
        {
            cnt++;
            lastans=i;
        }
    }
    return cnt+1<=m;
}

int main()
{
    scanf("%d %d",&n,&m);
    int maxa=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        sum[i]=sum[i-1]+a[i];
        maxa=maxa<a[i]?a[i]:maxa;
    }
    check(sum[n]);
    int l=maxa,r=sum[n],ans;
    while(l<r)
    {
        int mid=l+r>>1;
        if(check(mid))
        {
            ans=mid;
            r=mid;
        }
        else
            l=mid+1;
    }
    printf("%d\n",ans);
}