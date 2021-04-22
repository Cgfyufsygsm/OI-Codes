#include <cstdio>
#include <cctype>
#include <cstring>

typedef long long ll;

const ll maxn=105,p=1e9+7;
ll n,k;

struct Matrix
{
    ll a[maxn][maxn];
    Matrix()
    {
        memset(a,0,sizeof a);
    }
};

Matrix operator *(Matrix a,Matrix b)
{
    Matrix c;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int ij=1;ij<=n;ij++)
                c.a[i][j]=(c.a[i][j]+a.a[i][ij]*b.a[ij][j]%p+p)%p;
    return c;
}

Matrix ksm(Matrix a)
{
    Matrix ans;
    for(int i=1;i<=n;i++)
        ans.a[i][i]=1;
    for(;k>0;k>>=1)
    {
        if(k&1)
            ans=ans*a;
        a=a*a;
    }
    return ans;
}

ll read()
{
    char c=getchar();
    ll s=0,p=1;
    while(!isdigit(c))
    {
        if(c=='-')
            p=-p;
        c=getchar();
    }
    while(isdigit(c))
        s=10*s+c-'0',c=getchar();
    return s*p;
}

int main()
{
    n=read(),k=read();
    Matrix A;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            A.a[i][j]=read();
    Matrix B=ksm(A);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            printf("%lld ",B.a[i][j]);
        printf("\n");
    }
    return 0;
}