#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

using std::sort;
using std::unique;

const int maxn=1e4+5;

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

inline int max(int a,int b)
{
    return a>b?a:b;
}

struct ScanLine
{
    int l,r,h;
    int mark;
    bool operator<(const ScanLine &b)const
    {
        if(h==b.h)
            return mark>b.mark;
        return h<b.h;
    }
}line[maxn<<1];

int X[maxn<<1];
int n,W,H;

struct SegTree
{
    int val,tag;
}f[maxn<<3];

void pushdown(int i,int j,int k)
{
    f[L].tag+=f[k].tag,f[R].tag+=f[k].tag;
    f[L].val+=f[k].tag,f[R].val+=f[k].tag;
    f[k].tag=0;
    return;
}

void modify(int i,int j,int k,int l,int r,int d)
{
    if(X[j]<l || X[i]>r)
        return;
    if(X[i]>=l && X[j]<=r)
    {
        f[k].val+=d;
        f[k].tag+=d;
        return;
    }
    pushdown(i,j,k);
    modify(i,M,L,l,r,d);
    modify(M+1,j,R,l,r,d);
    f[k].val=max(f[L].val,f[R].val);
    return;
}

int main()
{
    int T=read();
    while(T--)
    {
        n=read(),W=read(),H=read();
        memset(line,0,sizeof line);
        memset(X,0,sizeof X);
        memset(f,0,sizeof f);
        for(int i=1;i<=n;i++)
        {
            int x=read(),y=read(),l=read();
            line[(i<<1)-1]=(ScanLine){x,x+W-1,y,l};
            line[i<<1]=(ScanLine){x,x+W-1,y+H-1,-l};
            X[(i<<1)-1]=x,X[i<<1]=x+W-1;
        }
        n<<=1;
        sort(line,line+n+1);
        sort(X,X+n+1);
        int tot=unique(X,X+n+1)-X-1;
        int ans=0;
        for(int i=1;i<n;i++)
        {
            modify(1,tot,1,line[i].l,line[i].r,line[i].mark);
            ans=max(ans,f[1].val);
        }
        printf("%d\n",ans);
    }
    return 0;
}