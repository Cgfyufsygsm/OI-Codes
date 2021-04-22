#include <cstdio>
#include <cctype>
#include <algorithm>

using namespace std;
typedef long long ll;

#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

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
int n,cnt,raw[maxn],a[maxn],f[maxn<<2];

void ins(int i,int j,int x,int k)
{
    if(i==j)
    {
        f[k]++;
        return;
    }
    if(x<=M)
        ins(i,M,x,L);
    else
        ins(M+1,j,x,R);
    f[k]=f[L]+f[R];
    return;
}

ll query(int i,int j,int x,int y,int k)
{
    if(x>y)
        return 0;
    if(x<=i && y>=j)
        return f[k];
    ll ans=0;
    if(x<=M)
        ans+=query(i,M,x,y,L);
    if(y>M)
        ans+=query(M+1,j,x,y,R);
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
        ins(1,cnt,cur,1);
        ans+=query(1,cnt,1,cur-1,1);
    }
    printf("%lld\n",ans);
}