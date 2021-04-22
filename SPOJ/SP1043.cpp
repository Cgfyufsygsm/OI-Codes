#include <cstdio>
#include <cctype>

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

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=50000+5;
int n,m;

struct segtree
{
    int pre,suf,ans,sum;
    segtree operator=(const int &x)
    {
        pre=suf=ans=sum=x;
        return *this;
    }
    segtree()
    {
        pre=suf=ans=sum=0;
    }
}f[maxn<<2];

segtree operator+(const segtree &a,const segtree &b)
{
    segtree ret;
    ret.sum=a.sum+b.sum;
    ret.pre=max(a.pre,a.sum+b.pre);
    ret.suf=max(b.suf,a.suf+b.sum);
    ret.ans=max(max(a.ans,b.ans),a.suf+b.pre);
    return ret;
}

void build(int i,int j,int k)
{
    if(i==j)
    {
        f[k]=read();
        return;
    }
    build(i,M,L);
    build(M+1,j,R);
    f[k]=f[L]+f[R];
    return;
}

segtree query(int i,int j,int x,int y,int k)
{
    if(x<=i && y>=j)
        return f[k];
    if(y<=M)
        return query(i,M,x,y,L);
    if(x>M)
        return query(M+1,j,x,y,R);
    return query(i,M,x,y,L)+query(M+1,j,x,y,R);
}


int main()
{
    n=read();
    build(1,n,1);
    m=read();
    while(m--)
    {
        int x=read(),y=read();
        printf("%d\n",query(1,n,x,y,1).ans);
    }
    return 0;
}