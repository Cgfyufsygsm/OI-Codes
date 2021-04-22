#include <cstdio>
#include <cctype>
#include <algorithm>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

using std::sort;
using std::unique;
typedef long long ll;

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

const int maxn=5005;
int n;

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
}line[2][maxn<<1];

ll pos[2][maxn<<1];

struct SegTree
{
    int sum;
    ll len;
}f[maxn<<2][2];

void pushup(int i,int j,int k,int p)
{
    if(f[k][p].sum)
        f[k][p].len=pos[p][j+1]-pos[p][i];
    else
        f[k][p].len=f[L][p].len+f[R][p].len;
    return;
}

void modify(int i,int j,int k,int l,int r,int p,int opt)
{
    if(pos[p][i]>=r || pos[p][j+1]<=l)
        return;
    if(pos[p][i]>=l && pos[p][j+1]<=r)
    {
        f[k][p].sum+=opt;
        pushup(i,j,k,p);
        return;
    }
    modify(i,M,L,l,r,p,opt);
    modify(M+1,j,R,l,r,p,opt);
    pushup(i,j,k,p);
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
        int x1=read(),y1=read(),x2=read(),y2=read();
        line[0][(i<<1)-1]=(ScanLine){x1,x2,y1,1};
        line[0][(i<<1)]=(ScanLine){x1,x2,y2,-1};
        line[1][(i<<1)-1]=(ScanLine){y1,y2,x1,1};
        line[1][(i<<1)]=(ScanLine){y1,y2,x2,-1};
        pos[0][(i<<1)-1]=x1,pos[0][i<<1]=x2;
        pos[1][(i<<1)-1]=y1,pos[1][i<<1]=y2;
    }
    n<<=1;
    sort(line[0]+1,line[0]+n+1);
    sort(line[1]+1,line[1]+n+1);
    sort(pos[0]+1,pos[0]+n+1);
    sort(pos[1]+1,pos[1]+n+1);
    int tot[2];
    tot[0]=unique(pos[0]+1,pos[0]+n+1)-pos[0]-1;
    tot[1]=unique(pos[1]+1,pos[1]+n+1)-pos[1]-1;
    ll ans=0;
    for(int p=0;p<2;p++)
    {
        ll lastans=0;
        for(int i=1;i<=n;i++)
        {
            modify(1,tot[p]-1,1,line[p][i].l,line[p][i].r,p,line[p][i].mark);
            ans+=abs(f[1][p].len-lastans);
            lastans=f[1][p].len;
        }
    }
    printf("%lld\n",ans);
    return 0;
}

