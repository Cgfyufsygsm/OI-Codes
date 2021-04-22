#include <cstdio>
#include <algorithm>
using std::sort;
using std::max;
typedef long long ll;

int n,t,f[100005];

struct food
{
    ll a,b,c;
}x[55];

bool cmp(food a,food b)
{
    return (ll)a.c*(ll)b.b<(ll)b.c*(ll)a.b;
}

int main()
{
    scanf("%d %d",&t,&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&x[i].a);
    for(int i=1;i<=n;i++)
        scanf("%lld",&x[i].b);
    for(int i=1;i<=n;i++)
        scanf("%lld",&x[i].c);
    sort(x+1,x+n+1,cmp);
    for(int i=1;i<=n;i++)
        for(int j=t;j-x[i].c>=0;j--)
            f[j]=max((ll)f[j],f[j-x[i].c]+x[i].a-j*x[i].b);
    int ans=0;
    for(int i=1;i<=t;i++)
        ans=max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}