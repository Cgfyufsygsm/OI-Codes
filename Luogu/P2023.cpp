#include <cstdio>
#include <cctype>
#define L (k<<1)
#define R (L|1)
typedef long long ll;

const int maxn=1e5+5;
ll n,m,p;
struct tree
{
    ll v,add,mul;
    int l,r;
}t[maxn<<2];

inline ll read()
{
    bool w=0;
    ll x=0;
    char c=getchar();
    while(!isdigit(c))
    {
        if(c=='-')
            w=1;
        c=getchar();
    }
    while(isdigit(c))
        x=x*10+c-'0',c=getchar();
    return w?-x:x;
}

void build(int i,int j,int k)
{
    t[k].mul=1,t[k].l=i,t[k].r=j;
    if(i==j)
    {
        t[k].v=read()%p;
        return;
    }
    int m=i+j>>1;
    build(i,m,L);
    build(m+1,j,R);
    t[k].v=(t[L].v+t[R].v)%p;
    return;
}

void down(int k)
{
    t[L].v=(t[L].v*t[k].mul%p+((t[L].r-t[L].l+1)*t[k].add)%p)%p;
    t[R].v=(t[R].v*t[k].mul%p+((t[R].r-t[R].l+1)*t[k].add)%p)%p;

    t[L].mul=t[L].mul*t[k].mul%p;
    t[R].mul=t[R].mul*t[k].mul%p;

    t[L].add=(t[L].add*t[k].mul+t[k].add)%p;
    t[R].add=(t[R].add*t[k].mul+t[k].add)%p;

    t[k].add=0,t[k].mul=1;
    return;
}

void add(int x,int y,int k,int d)
{
    int l=t[k].l,r=t[k].r;
    if(l>=x && r<=y)
    {
        t[k].add=(t[k].add+d)%p;
        t[k].v=(t[k].v+(r-l+1)*d)%p;
        return;
    }
    down(k);
    int m=l+r>>1;
    if(x<=m)
        add(x,y,L,d);
    if(y>m)
        add(x,y,R,d);
    t[k].v=(t[L].v+t[R].v)%p;
    return;
}

void mul(int x,int y,int k,int d)
{
    int l=t[k].l,r=t[k].r;
    if(l>=x && r<=y)
    {
        t[k].add=t[k].add*d%p;
        t[k].mul=t[k].mul*d%p;
        t[k].v=t[k].v*d%p;
        return;
    }
    down(k);
    int m=l+r>>1;
    if(x<=m)
        mul(x,y,L,d);
    if(y>m)
        mul(x,y,R,d);
    t[k].v=(t[L].v+t[R].v)%p;
    return;
}

ll ask(int x,int y,int k)
{
    int l=t[k].l,r=t[k].r,m=l+r>>1;
    if(l>=x && r<=y)
        return t[k].v;
    down(k);
    ll ans=0;
    if(x<=m)
        ans+=ask(x,y,L);
    if(y>m)
        ans+=ask(x,y,R);
    return ans%p;
}

int main()
{
    n=read(),p=read();
    build(1,n,1);
    m=read();
    int c,x,y,k;
    while(m--)
    {
        c=read(),x=read(),y=read();
        if(c==1)
        {
            k=read();
            mul(x,y,1,k);
        }
        else if(c==2)
        {
            k=read();
            add(x,y,1,k);
        }
        else
            printf("%lld\n",ask(x,y,1));
    }
    return 0;
}