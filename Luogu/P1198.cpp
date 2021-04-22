#include <iostream>
#define L (k<<1)
#define R (L|1)
typedef long long ll;
using namespace std;

inline ll max(ll a,ll b)
{
    return a>b?a:b;
}

const int maxn=2e5+5;
int m,d,tot;
ll f[maxn<<2];

ll query(int i,int j,int x,int y,int k)
{
    //printf("i:%d,j:%d,x:%d,y:%d,k:%d\n",i,j,x,y,k);
    if(i>=x &&j<=y)
        return f[k];
    int m=i+j>>1;
    ll ans=0;
    if(x<=m)
        ans=max(ans,query(i,m,x,y,L));
    if(y>m)
        ans=max(ans,query(m+1,j,x,y,R));
    return ans;
}

void add(int i,int j,int x,int k,int d)
{
    if(i==j && i==x)
    {
        f[k]=d;
        return;
    }
    int m=i+j>>1;
    if(x<=m)
        add(i,m,x,L,d);
    else
        add(m+1,j,x,R,d);
    f[k]=max(f[L],f[R]);
    return;
}

int main()
{
    //freopen("1.out","w",stdout);
    ios::sync_with_stdio(false);
    cin>>m>>d;
    char c;
    int n=0,t=0;
    for(int i=1;i<=m;i++)
    {
        cin>>c>>n;
        if(c=='Q')
        {
            t=query(1,m,tot-n+1,tot,1);
            cout<<t<<endl;
        }
        if(c=='A')
            add(1,m,++tot,1,(n+t)%d);
    }
    return 0;
}