#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cmath>
#define L (k<<1)
#define R (L|1)
#define M (i+j>>1)
typedef long long ll;

const int maxn=1e5+5;
int kase=0;

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

class segtree
{
private:
    ll f[maxn<<2];
    int n,m;
    void clear()
    {
        n=0,m=0;
        memset(f,0,sizeof(f));
        return;
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
    }
    void modify(int i,int j,int l,int r,int k)
    {
        if(i==j)
        {
            f[k]=sqrt(f[k]);
            return;
        }
        if(f[k]==j-i+1)
            return;
        if(l<=M)
            modify(i,M,l,r,L);
        if(r>M)
            modify(M+1,j,l,r,R);
        f[k]=f[L]+f[R];
        return;
    }
    ll ask(int i,int j,int l,int r,int k)
    {
        if(i>=l && j<=r)
            return f[k];
        ll ans=0;
        if(l<=M)
            ans+=ask(i,M,l,r,L);
        if(r>M)
            ans+=ask(M+1,j,l,r,R);
        return ans;
    }
public:
    void solve()
    {
        clear();
        if(scanf("%d",&n)==EOF)
            exit(0);
        printf("Case #%d:\n",++kase);
        build(1,n,1);
        m=read();
        int t,x,y;
        while(m--)
        {
            t=read(),x=read(),y=read();
            if(x>y)
            {
                int k=x;
                x=y;
                y=k;
            }
            if(t)
                printf("%lld\n",ask(1,n,x,y,1));
            else
                modify(1,n,x,y,1);
        }
        printf("\n");
    }
}t;

int main()
{
    //freopen("s.out","w",stdout);
    while(1)
        t.solve();
    return 0;
}