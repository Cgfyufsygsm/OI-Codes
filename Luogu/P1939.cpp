#include <cstdio>
#include <cctype>
#include <cstring>

typedef long long ll;
const ll p=1e9+7;

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

struct Matrix
{
    ll a[4][4];
    Matrix()
    {
        memset(a,0,sizeof a);
    }
    void set()
    {
        memset(a,0,sizeof a);
        for(int i=1;i<=3;i++)
            a[i][i]=1;
    }
    void set2()
    {
        memset(a,0,sizeof a);
        a[1][1]=a[1][3]=a[2][1]=a[3][2]=1;
    }
};

Matrix operator* (Matrix a,Matrix b)
{
    Matrix c;
    for(int k=1;k<=3;k++)
        for(int i=1;i<=3;i++)
            for(int j=1;j<=3;j++)
                c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%p)%p;
    return c;
}

int main()
{
    int T=read();
    while(T--)
    {
        int n=read();
        Matrix ans,base;
        ans.set(),base.set2();
        for(;n>0;n>>=1)
        {
            if(n&1)
                ans=ans*base;
            base=base*base;
        }
        printf("%lld\n",ans.a[2][1]);
    }
    return 0;
}