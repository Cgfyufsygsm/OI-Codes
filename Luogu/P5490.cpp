#include <cstdio>
#include <cctype>
#include <algorithm>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

typedef long long ll;
using std::sort;
using std::unique;
using std::lower_bound;
const int maxn=1e6+5;

int n;

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

struct ScanLine
{
    ll l,r,h;
    int mark;
    bool operator<(const ScanLine &b)const
    {
        return h<b.h;
    }
}line[maxn<<1];

ll X[maxn<<1];

struct SegTree
{
    int sum;//完全覆盖的线段个数
    ll len;//区间被覆盖的长度
}f[maxn<<2];

void build(int i,int j,int k)
{
    f[k].sum=f[k].len=0;
    if(i==j)
        return;
    build(i,M,L);
    build(M+1,j,R);
    return;
}

void pushup(int i,int j,int k)
{
    if(f[k].sum)
        f[k].len=X[j+1]-X[i];//如果被完全覆盖
    else
        f[k].len=f[L].len+f[R].len;//合并子区间
    return;
}

void modify(int i,int j,int k,int l,int r,int opt)
{
    if(X[j+1]<=l || X[i]>=r)
        return;
    if(l<=X[i] && X[j+1]<=r)
    {
        f[k].sum+=opt;
        pushup(i,j,k);
        return;
    }
    modify(i,M,L,l,r,opt);
    modify(M+1,j,R,l,r,opt);
    pushup(i,j,k);
    return;
}

int main()
{
    n=read();
    for(int i=1;i<=n;++i)
    {
        ll x1=read(),y1=read(),x2=read(),y2=read();
        X[(i<<1)-1]=x1,X[i<<1]=x2;
        line[(i<<1)-1]=(ScanLine){x1,x2,y1,1};
        line[i<<1]=(ScanLine){x1,x2,y2,-1};
    }
    n<<=1;
    sort(line+1,line+n+1);
    sort(X+1,X+n+1);
    int tot=unique(X+1,X+n+1)-X-1;
    build(1,tot-1,1);
    ll ans=0;
    for(int i=1;i<n;++i)
    {
        modify(1,tot-1,1,line[i].l,line[i].r,line[i].mark);
        ans+=f[1].len*(line[i+1].h-line[i].h);
    }
    printf("%lld\n",ans);
    return 0;
}