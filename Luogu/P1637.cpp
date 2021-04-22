#include <cstdio>
#include <cctype>
#include <algorithm>

#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

using namespace std;
typedef long long ll;

inline ll read()
{
    char c = getchar();
    ll s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

const int maxn=3e4+5;
ll raw[maxn],a[maxn];
ll f1[maxn<<2],f2[maxn<<2],n,len; 

void ins1(int i,int j,int k,int x)
{
    if(i==j)
    {
        f1[k]++;
        return;
    }
    if(x<=M)
        ins1(i,M,L,x);
    else
        ins1(M+1,j,R,x);
    f1[k]=f1[L]+f1[R];
    return;
}

ll ask1(int i,int j,int x,int y,int k)
{
    if(x<=i && y>=j)
        return f1[k];
    ll ret=0;
    if(x<=M)
        ret+=ask1(i,M,x,y,L);
    if(y>M)
        ret+=ask1(M+1,j,x,y,R);
    return ret;
}

void ins2(int i,int j,int k,int x,int d)
{
    if(i==j)
    {
        f2[k]+=d;
        return;
    }
    if(x<=M)
        ins2(i,M,L,x,d);
    else
        ins2(M+1,j,R,x,d);
    f2[k]=f2[L]+f2[R];
    return;
}

ll ask2(int i,int j,int x,int y,int k)
{
    if(x<=i && y>=j)
        return f2[k];
    ll ret=0;
    if(x<=M)
        ret+=ask2(i,M,x,y,L);
    if(y>M)
        ret+=ask2(M+1,j,x,y,R);
    return ret;
}

int main()
{
    n=read();
    if(n<3)
    {
        printf("0\n");
        return 0;
    }
    for(int i=1;i<=n;i++)
        raw[i]=a[i]=read();
    sort(a+1,a+1+n);
    len=unique(a+1,a+1+n)-a-1;
    ll ans=0;
    for(int i=n;i>=1;i--)
    {
        int cur=lower_bound(a+1,a+len+1,raw[i])-a;
        ins1(1,len,1,cur);
        if(i<n)
            ins2(1,len,1,cur,ask1(1,len,cur+1,len,1));
        if(i<n-1)
            ans+=ask2(1,len,cur+1,len,1);
    }
    printf("%lld\n",ans);
    return 0;
}