#include <cstdio>
#include <cctype>
typedef long long ll;

const int maxn=1e7+5;
ll a[maxn],d1[maxn],d2[maxn];

inline ll read()
{
    char c = getchar();
    ll s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

int main()
{
    int n=read(),m=read();
    ll l,r,s,e;
    while(m--)
    {
        l=read(),r=read(),s=read(),e=read();
        int d=(e-s)/(r-l);
        d2[l]+=s;
        d2[l+1]+=d-s;
        d2[r+1]-=e+d;
        d2[r+2]+=e;
    }
    ll maxans=0,ans=0;
    for(int i=1;i<=n;i++)
    {
        d1[i]=d1[i-1]+d2[i],a[i]=a[i-1]+d1[i];
        maxans=maxans<a[i]?a[i]:maxans;
        ans^=a[i];
    }
    printf("%lld %lld\n",ans,maxans);
    return 0;
}