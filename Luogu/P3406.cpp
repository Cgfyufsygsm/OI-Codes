#include <cstdio>
#include <algorithm>
typedef long long ll;
using namespace std;

const int maxn=1e5+5;
int n,m;
ll p[maxn],a[maxn],b[maxn],c[maxn];
ll time[maxn];//每条铁路乘坐次数的差分数组
//i铁路连接i和i+1

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%lld",&p[i]);
    for(int i=1;i<n;i++)
        scanf("%lld %lld %lld",&a[i],&b[i],&c[i]);
    for(int i=1;i<m;i++)
    {
        int l=min(p[i],p[i+1]),r=max(p[i],p[i+1]);
        time[l]++,time[r]--;
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        time[i]+=time[i-1];
        if(a[i]*time[i]>c[i]+b[i]*time[i])
            ans+=c[i]+b[i]*time[i];
        else
            ans+=a[i]*time[i];
    }
    printf("%lld\n",ans);
}