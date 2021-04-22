#include <cstdio>
#include <cctype>
#include <algorithm>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

using std::max;

const int maxn=1e5+5;

int f1[maxn<<2],n,m;
double f2[maxn<<2];
double a[maxn];

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

int pushup(double mk,int i,int j,int k)
{
    if(f2[k]<=mk)
        return 0;
    if(a[i]>mk)
        return f1[k];
    if(i==j)
        return f2[k]>mk;
    if(f2[L]<=mk)
        return pushup(mk,M+1,j,R);
    return pushup(mk,i,M,L)+f1[k]-f1[L];
}


void modify(int i,int j,int x,double d,int k)
{
    if(i==j&&i==x)
    {
        f1[k]=1;
        f2[k]=d;
        return;
    }
    if(x<=M)
        modify(i,M,x,d,L);
    if(x>M)
        modify(M+1,j,x,d,R);
    f2[k]=max(f2[L],f2[R]);
    f1[k]=f1[L]+pushup(f2[L],M+1,j,R);
    return;
}

int main()
{
    n=read(),m=read();
    int x,y;
    for(int i=1;i<=m;i++)
    {
        x=read(),y=read();
        a[x]=(double)y/(double)x;
        modify(1,n,x,a[x],1);
        printf("%d\n",f1[1]);
    }
    return 0;
}