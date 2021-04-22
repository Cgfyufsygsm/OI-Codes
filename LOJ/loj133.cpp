#include <cstdio>
#define lowbit(x) (x&-x)
typedef long long ll;

const int maxn=(1<<12)+5;
int n,m;
ll f[maxn][maxn];

void add(int x,int y,int d)
{
    for(int xx=x;xx<=n;xx+=lowbit(xx))
        for(int yy=y;yy<=m;yy+=lowbit(yy))
            f[xx][yy]+=d;
    return;
}

ll sum(int x,int y)
{
    ll ans=0;
    for(;x>0;x-=lowbit(x))
        for(int yy=y;yy>0;yy-=lowbit(yy))
            ans+=f[x][yy];
    return ans;
}

int main()
{
    scanf("%d %d",&n,&m);
    int t,a,b,c,d,k;
    while(scanf("%d",&t)!=EOF)
    {
        if(t==1)
        {
            scanf("%d %d %d",&a,&b,&k);
            add(a,b,k);
        }
        else
        {
            scanf("%d %d %d %d",&a,&b,&c,&d);
            ll ans=sum(c,d)-sum(a-1,d)-sum(c,b-1)+sum(a-1,b-1);
            printf("%lld\n",ans);
        }
    }
    return 0;
}