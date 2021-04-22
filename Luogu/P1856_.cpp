#include <cstdio>
#include <cctype>
#include <algorithm>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

typedef long long ll;
using std::sort;
using std::unique;
const int maxn=5005;

int n;

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

struct ScanLine
{
    ll l,r,h;
    int mark;
    bool operator<(const ScanLine &b)const
    {
        if(h==b.h)
            return mark>b.mark;
        return h<b.h;
    }
}line[maxn<<1];

ll X[maxn<<1];

struct SegTree
{
    int sum;//完全覆盖的线段个数
    int num;//覆盖了的线段条数
    ll len;//区间被覆盖的长度
    bool lflag,rflag;//表示左/右端点是否被覆盖
}f[maxn<<2];

void pushup(int i,int j,int k)
{
    if(f[k].sum)
    {
        f[k].lflag=f[k].rflag=1;
        f[k].num=1;
        f[k].len=X[j+1]-X[i];//如果被完全覆盖
    }
    else
    {
        f[k].lflag=f[L].lflag;
        f[k].rflag=f[R].rflag;
        f[k].num=f[L].num+f[R].num;
        if(f[L].rflag && f[R].lflag)
            --f[k].num;
        f[k].len=f[L].len+f[R].len;
    }
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

inline int abs(int x)
{
    return x>=0?x:-x;
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
    ll ans=0,lastans=0;
    for(int i=1;i<=n;++i)
    {
        modify(1,tot-1,1,line[i].l,line[i].r,line[i].mark);
        if(i<n)ans+=f[1].num*2*(line[i+1].h-line[i].h);
        ans+=abs(f[1].len-lastans);
        lastans=f[1].len;
    }
    //ans+=line[n].r-line[n].l;
    printf("%lld\n",ans);
    return 0;
}