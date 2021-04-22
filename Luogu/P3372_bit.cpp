#include <cstdio>
#define lowbit(x) (x&-x)
typedef long long ll;

const int maxn=1e5+5;

ll a[maxn],c[maxn],t1[maxn],t2[maxn],n,m;

inline ll read()
{
    ll s=0;
    bool symbol=0;
    char c=getchar();
    while(c < '0' || c > '9')
    {
        if(c=='-') symbol=1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
        s=s*10+c-'0',c=getchar();
    if(symbol) s=-s;
    return s;
}

void upd(int x,ll k)
{
    ll k1=k*(ll)x;
    while(x<=n) t1[x]+=k,t2[x]+=k1,x+=lowbit(x);
    return;
}

void build()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        c[i]=a[i]-a[i-1];
        upd(i,c[i]);
    }
    return;
}

void modify(int x,int y,ll k)
{
    upd(x,k),upd(y+1,-k);
    return;
}

ll query(ll *t,int x)//取[1,x]
{
    ll ans=0;
    for(;x>0;x-=lowbit(x)) ans+=t[x];
    return ans;
}

ll sum1(int r)
{
    return (r+1ll)*query(t1,r)-query(t2,r);
}

ll sum(int x,int y)
{
    return (sum1(y))-(sum1(x-1));
}

int main()
{
    //freopen("1.in","r",stdin);
    build();
    for(int i=1;i<=m;i++)
    {
        ll t=read(),x=read(),y=read(),k;
        if(t==1)
        {
            k=read();
            modify(x,y,k);
        }
        if(t==2) printf("%lld\n",sum(x,y));
    }
    return 0;
}
