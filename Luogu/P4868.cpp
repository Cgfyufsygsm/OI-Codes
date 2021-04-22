#include <cstdio>
#include <cctype>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)
typedef long long ll;

const int maxn=100005;
ll a[maxn],s[maxn],f[maxn<<2],tag[maxn<<2];

int n,m;

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

void build(int i,int j,int k)
{
    if(i==j)
    {
        a[i]=read();
        s[i]=s[i-1]+a[i];
        f[k]=s[i];
        return;
    }
    build(i,M,L);
    build(M+1,j,R);
    f[k]=f[L]+f[R];
    return;
}

inline void down(int i,int j,int k)
{
    f[L]+=tag[k]*(M-i+1ll);
    f[R]+=tag[k]*(ll)(j-M);
    tag[L]+=tag[k];
    tag[R]+=tag[k];
    tag[k]=0;
    return;
}

void modify(int i,int j,int l,int r,int k,int d)
{
    if(i>=l && j<=r)
    {
        f[k]+=d*(j-i+1ll);
        tag[k]+=d;
        return;
    }
    if(tag[k])
        down(i,j,k);
    if(l<=M)
        modify(i,M,l,r,L,d);
    if(r>M)
        modify(M+1,j,l,r,R,d);
    f[k]=f[L]+f[R];
    return;
}

ll ask(int i,int j,int l,int r,int k)
{
    if(i>=l && j<=r)
        return f[k];
    if(tag[k])
        down(i,j,k);
    ll ans=0;
    if(l<=M)
        ans+=ask(i,M,l,r,L);
    if(r>M)
        ans+=ask(M+1,j,l,r,R);
    return ans;
}

int main()
{
    n=read(),m=read();
    build(1,n,1);
    char opt[10];
    int i;
    while(m--)
    {
        scanf("%s %d",opt,&i);
        if(opt[0]=='M')
        {
            ll x=read();
            modify(1,n,i,n,1,x-a[i]);
            a[i]=x;
        }
        else
            printf("%lld\n",ask(1,n,1,i,1));
    }
    return 0;
}