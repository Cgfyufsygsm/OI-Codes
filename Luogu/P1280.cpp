#include <cstdio>
#include <algorithm>
using std::sort;

const int maxn=1e4+5;

struct task
{
    int p,t;//p为起始时间，t为持续时间
}t[maxn];

bool cmp(task a,task b)
{
    return a.p>b.p;
}

int n,k,f[maxn],sum[maxn];

int main()
{
    scanf("%d %d",&n,&k);
    int pp,tt;
    for(int i=1;i<=k;i++)
    {
        scanf("%d %d",&pp,&tt);
        t[i].p=pp,t[i].t=tt;
        sum[pp]++;
    }
    int num=1;
    sort(t+1,t+k+1,cmp);
    for(int i=n;i>=1;i--)
    {
        if(!sum[i])
            f[i]=f[i+1]+1;
        else for(int j=1;j<=sum[i];j++)
        {
            if(f[i+t[num].t]>f[i])
                f[i]=f[i+t[num].t];
            num++;
        }
    }
    printf("%d\n",f[1]);
    return 0;
}