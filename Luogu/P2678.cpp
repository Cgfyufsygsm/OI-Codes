#include <cstdio>

int L,n,m,d[50005];

bool judge(int x)
{
    int cnt=0;
    int now=0,i=0;
    while(i<n+1)
    {
        ++i;
        if(d[i]-d[now]<x)
            cnt++;
        else
            now=i;
    }
    return cnt<=m;
}

int binary()
{
    int l=1,r=L;
    int ans;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(judge(mid))
            ans=mid,l=mid+1;
        else
            r=mid-1;
    }
    return ans;
}

int main()
{
    scanf("%d %d %d",&L,&n,&m);
    d[0]=0;
    for(int i=1;i<=n;i++) scanf("%d",d+i);
    d[n+1]=L;
    printf("%d\n",binary());
    return 0;
}