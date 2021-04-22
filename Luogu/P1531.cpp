#include <iostream>
#define L (k<<1)
#define R (L|1)
#define M (i+j>>1)
using namespace std;

const int maxn=2e5+5;
int f[maxn<<2],a[maxn],n,m;

inline int max(int a,int b)
{
    return a>b?a:b;
}

void build(int i,int j,int k)
{
    if(i==j)
    {
        cin>>a[i];
        f[k]=a[i];
        return;
    }
    build(i,M,L);
    build(M+1,j,R);
    f[k]=max(f[L],f[R]);
}

void modify(int i,int j,int x,int k,int d)
{
    if(i==j && i==x)
    {
        a[i]=d;
        f[k]=d;
        return;
    }
    if(x<=M)
        modify(i,M,x,L,d);
    else
        modify(M+1,j,x,R,d);
    f[k]=max(f[L],f[R]);
    return;
}

int ask(int i,int j,int l,int r,int k)
{
    if(l<=i && r>=j)
        return f[k];
    int ans=0;
    if(l<=M)
        ans=max(ans,ask(i,M,l,r,L));
    if(r>M)
        ans=max(ans,ask(M+1,j,l,r,R));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    build(1,n,1);
    char c;
    int x,y;
    while(m--)
    {
        cin>>c>>x>>y;
        if(c=='U' && a[x]<y)
            modify(1,n,x,1,y);
        if(c=='Q')
            cout<<ask(1,n,x,y,1)<<endl;
    }
    return 0;
}