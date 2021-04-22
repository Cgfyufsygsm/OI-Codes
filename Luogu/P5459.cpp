#include <cstdio>
#include <cctype>
#define LS (f[k].lson)
#define RS (f[k].rson)
#define M ((i+j)>>1)

typedef long long ll;

inline ll read()
{
    char c = getchar();
    ll s = 0, x = 0;
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

const ll maxn=1e5+5,maxm=1e10;
ll sum[maxn],n,l,r,cnt;

struct SegTree
{
    int lson,rson;
    ll val;
    SegTree(){lson=rson=val=0;}
}f[(int)8e6+5];

void insert(ll i,ll j,int &k,ll x)
{
    if(!k)
        k=++cnt;
    if(i==j)
    {
        ++f[k].val;
        return;
    }
    if(x<=M)
        insert(i,M,LS,x);
    else
        insert(M+1,j,RS,x);
    f[k].val=f[LS].val+f[RS].val;
}

ll query(ll i,ll j,int &k,ll x,ll y)
{
    if(!k)
        k=++cnt;
    if(x<=i && y>=j)
        return f[k].val;
    ll ret=0;
    if(x<=M)
        ret+=query(i,M,LS,x,y);
    if(y>M)
        ret+=query(M+1,j,RS,x,y);
    return ret;
}

int main()
{
    n=read(),l=read(),r=read();
    ll ans=0;
    int root=1;
    insert(-maxm,maxm,root,0);
    for(int i=1;i<=n;i++)
    {
        sum[i]=sum[i-1]+read();
        ans+=query(-maxm,maxm,root,sum[i]-r,sum[i]-l);
        insert(-maxm,maxm,root,sum[i]);
    }
    printf("%lld\n",ans);
    return 0;
}