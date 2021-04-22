#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

using std::sort;
using std::lower_bound;
using std::unique;

typedef long long ll;
const int maxn=1e6+5;
ll a[maxn<<1];
int n,tot;

struct sol
{
    int fa[maxn<<1];
    void init()
    {
        for(int i=1;i<=tot;i++)
            fa[i]=i;
        return;
    }
    int find(int x)
    {
        return x==fa[x]?x:fa[x]=find(fa[x]);
    }
    void uni(int x,int y)
    {
        fa[find(x)]=find(y);
    }
    bool query(int x,int y)
    {
        return find(x)==find(y);
    }
}u;

struct node
{
    ll i,j;
    bool e;
    bool operator<(const node &b)const
    {
        return e>b.e;
    }
}req[maxn];

inline ll read()
{
    char c = getchar();
    ll s = 0, x = 0;
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

int main()
{
    int t=read();
    while(t--)
    {
        n=read();
        memset(a,0,sizeof a);
        int cnt=0;
        for(int i=1;i<=n;i++)
        {
            req[i].i=read(),req[i].j=read(),req[i].e=read();
            cnt+=req[i].e;
            a[(i<<1)-1]=req[i].i;
            a[i<<1]=req[i].j;
        }
        sort(req+1,req+1+n);
        sort(a+1,a+(n<<1)+1);
        tot=unique(a+1,a+(n<<1)+1)-a-1;
        u.init();
        bool flag=1;
        for(int i=1;i<=cnt;i++)
        {
            int x=lower_bound(a+1,a+tot+1,req[i].i)-a,y=lower_bound(a+1,a+tot+1,req[i].j)-a;
            u.uni(x,y);
        }
        for(int i=cnt+1;i<=n;i++)
        {
            int x=lower_bound(a+1,a+tot+1,req[i].i)-a,y=lower_bound(a+1,a+tot+1,req[i].j)-a;
            if(u.query(x,y))
            {
                flag=0;
                break;
            }
        }
        printf("%s\n",flag?"YES":"NO");
    }
    return 0;
}