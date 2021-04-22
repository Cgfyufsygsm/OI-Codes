#include <cstdio>
#include <cmath>
#include <cctype>
#define L (k<<1)
#define R (L|1)
typedef long long ll;

const int maxn=100005;
int n,m;
ll f[maxn<<2];

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

inline void swap(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
}

void build(int i,int j,int k)
{
    if(i==j)
    {
        f[k]=read();
        return;
    }
    int m=i+j>>1;
    build(i,m,L);
    build(m+1,j,R);
    f[k]=f[L]+f[R];
    return;
}

void modify(int i,int j,int x,int y,int k)
{
    if(i==j && i>=x && j<=y)
    {
        f[k]=sqrt(f[k]);
        return;
    }
    if(f[k]==j-i+1)
        return;
    int m=i+j>>1;
    if(x<=m)
        modify(i,m,x,y,L);
    if(y>m)
        modify(m+1,j,x,y,R);
    f[k]=f[L]+f[R];
    return;
}

ll ask(int i,int j,int x,int y,int k)
{
    //printf("i:%d,j:%d,k:%d,x:%d,y:%d\n",i,j,k,x,y);
    if(x<=i && y>=j)
        return f[k];
    ll ans=0;
    int m=i+j>>1;
    if(x<=m)
        ans+=ask(i,m,x,y,L);
    if(y>m)
        ans+=ask(m+1,j,x,y,R);
    return ans;
}

int main()
{
    //freopen("1.out","w",stdout);
    n=read();
    build(1,n,1);
    m=read();
    int k,l,r;
    while(m--)
    {
        k=read(),l=read(),r=read();
        if(l>r)
            swap(l,r);
        if(k)
            printf("%lld\n",ask(1,n,l,r,1));
        else
            modify(1,n,l,r,1);
    }
    return 0;
}