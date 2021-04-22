#include <cstdio>
#include <cctype>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

typedef unsigned int uint;
const int maxn=100000+5;

struct tree
{
    uint x;
    int tag;
    tree operator+(const tree &b)const
    {
        //printf("%d|%d\n",this->x,b.x);
        return (tree){this->x|b.x,0};
    }
}f[maxn<<2];

int n,m,k;

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

inline char readchar()
{
    char c=getchar();
    while(!isalpha(c))
        c=getchar();
    return c;
}

void build(int i,int j,int k)
{
    if(i==j)
    {
        f[k].x=1;
        return;
    }
    build(i,M,L);
    build(M+1,j,R);
    f[k]=f[L]+f[R];
    return;
}

void down(int i,int j,int k)
{
    f[L].x=f[R].x=1<<(f[k].tag-1);
    f[L].tag=f[R].tag=f[k].tag;
    f[k].tag=0;
    return;
}

void modify(int i,int j,int k,int x,int y,int d)
{
    if(x<=i && y>=j)
    {
        f[k].x=1<<(d-1);
        f[k].tag=d;
        return;
    }
    if(f[k].tag)
        down(i,j,k);
    if(x<=M)
        modify(i,M,L,x,y,d);
    if(y>M)
        modify(M+1,j,R,x,y,d);
    f[k]=f[L]+f[R];
    return;
}

tree query(int i,int j,int k,int x,int y)
{
    //printf("%d %d %d %d\n",i,j,x,y);
    if(x<=i && y>=j)
        return f[k];
    if(f[k].tag)
        down(i,j,k);
    if(y<=M)
        return query(i,M,L,x,y);
    if(x>M)
        return query(M+1,j,R,x,y);
    return query(i,M,L,x,y)+query(M+1,j,R,x,y);
}

int calc(int x)
{
    int ret=0;
    while(x)
    {
        ret+=(x&1);
        x>>=1;
    }
    return ret;
}

int main()
{
    n=read(),k=read(),m=read();
    build(1,n,1);
    char tmp;
    while(m--)
    {
        tmp=readchar();
        if(tmp=='C')
        {
            int l=read(),r=read(),x=read();
            if(l>r)
                modify(1,n,1,r,l,x);
            else
                modify(1,n,1,l,r,x);
        }
        if(tmp=='P')
        {
            int x=read(),y=read();
            if(x>y)
                printf("%d\n",calc(query(1,n,1,y,x).x));
            else
                printf("%d\n",calc(query(1,n,1,x,y).x));
        }
    }
    return 0;
}