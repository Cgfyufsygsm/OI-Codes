#include <cstdio>
#include <cctype>
#include <algorithm>

using namespace std;
typedef long long ll;

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
    {
        if(c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline bool cmp(int &a,int &b)
{
    return a>b;
}

const int maxn=5e5+5;
int n,cnt,raw[maxn],a[maxn],f[maxn];

void ins(int x)
{
    for(;x<=cnt;x+=(x&-x))
        f[x]++;
    return;
}

ll query(int x)
{
    ll ans=0;
    for(;x;x-=(x&-x))
        ans+=f[x];
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=raw[i]=read();
    sort(a+1,a+n+1);
    cnt=unique(a+1,a+n+1)-a-1;
    ll ans=0;
    for(int i=n;i>=1;i--)
    {
        int cur=lower_bound(a+1,a+cnt+1,raw[i])-a;
        ins(cur);
        ans+=query(cur-1);
    }
    printf("%lld\n",ans);
}