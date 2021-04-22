#include <cstdio>
#include <cctype>
#include <cstring>

#define f(i,a,b) for(int i=a;i<=b;i++)

typedef long long ll;

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

const ll maxn=105,maxm=2.5e3+5;
ll n,m,k,t[maxm],u[maxm],v[maxm];
ll d[maxn][maxn];

struct matrix
{
    int n;
    ll a[maxn][maxn];
}a;

matrix operator*(const matrix &x,const matrix &y)
{
    matrix ret;
    ret.n=x.n;
    memset(ret.a,0x3f,sizeof ret.a);
    f(k,1,ret.n)
        f(i,1,ret.n)
            f(j,1,ret.n)
                if(x.a[i][k]+y.a[k][j]<ret.a[i][j])
                    ret.a[i][j]=x.a[i][k]+y.a[k][j];
    return ret;
}

matrix qpower(matrix x,int k)
{
    matrix ans;
    ans.n=x.n;
    f(i,1,x.n)
        f(j,1,x.n)
            ans.a[i][j]=d[i][j];
    for(;k;k>>=1)
    {
        if(k&1)
            ans=ans*x;
        x=x*x;
    }
    return ans;
}

int main()
{
    n=read(),m=read(),k=read();
    memset(d,0x3f,sizeof d);
    f(i,1,n)
        d[i][i]=0;
    f(i,1,m)
    {
        u[i]=read(),v[i]=read(),t[i]=read();
        d[u[i]][v[i]]=t[i];
        //G[read()][read()]=read();
    }
    f(k,1,n)
        f(i,1,n)
            f(j,1,n)
                if(d[i][j]>d[i][k]+d[k][j])
                    d[i][j]=d[i][k]+d[k][j];
    if(!k)
    {
        printf("%lld\n",d[1][n]);
        return 0;
    }
    a.n=n;
    f(i,1,n)
        f(j,1,n)
            a.a[i][j]=d[i][j];
    f(k,1,m)
        f(i,1,n)
            f(j,1,n)
                if(a.a[i][j]>d[i][u[k]]+d[v[k]][j]-t[k])
                    a.a[i][j]=d[i][u[k]]+d[v[k]][j]-t[k];
    printf("%lld\n",qpower(a,k).a[1][n]);
    return 0;
}