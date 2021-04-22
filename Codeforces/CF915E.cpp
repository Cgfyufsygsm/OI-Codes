#include <cstdio>
#include <cctype>
#define L (f[k].lson)
#define R (f[k].rson)
#define M ((i+j)>>1)

using namespace std;

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

const int maxn=300005*55;

struct SegTree
{
    int lson,rson,tag,val;
    SegTree()
    {
        tag=-1;
        val=0;
        lson=rson=0;
    }
}f[maxn];

int n,cnt=1;

void down(int i,int j,int k)
{
    if(!L)
        L=++cnt;
    if(!R)
        R=++cnt;
    f[L].val=(M-i+1)*f[k].tag;
    f[L].tag=f[k].tag;
    f[R].val=(j-M)*f[k].tag;
    f[R].tag=f[k].tag;
    f[k].tag=-1;
}

void modify(int i,int j,int &k,int x,int y,int opt)
{
    if(!k)
        k=++cnt;
    if(x<=i && y>=j)
    {
        f[k].val=(j-i+1)*opt;
        f[k].tag=opt;
        return;
    }
    if(f[k].tag!=-1)
        down(i,j,k);
    if(x<=M)
        modify(i,M,L,x,y,opt);
    if(y>M)
        modify(M+1,j,R,x,y,opt);
    f[k].val=f[L].val+f[R].val;
    return;
}

int main()
{
    n=read();
    int q=read(),root=1;
    f[root].val=n,f[root].tag=1;
    while(q--)
    {
        int l=read(),r=read(),k=read()-1;
        modify(1,n,root,l,r,k);
        printf("%d\n",f[root].val);
    }
    return 0;
}
