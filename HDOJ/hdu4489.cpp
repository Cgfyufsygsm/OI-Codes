#include <cstdio>
#include <cctype>
#include <cstring>

typedef unsigned long long ll;

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

ll f[21][2],c[21][21],p,d,n,cnt;

int main()
{
    for(int i=1;i<=20;i++)
    {
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++)
            c[i][j]=c[i-1][j]+c[i-1][j-1];
    }
    f[1][1]=f[0][1]=f[1][0]=f[0][0]=1;
    for(int i=2;i<=20;i++)
    {
        ll tot=0;
        for(int j=0;j<i;j++)
            tot+=f[j][0]*f[i-j-1][1]*c[i-1][j];
        f[i][0]=f[i][1]=tot/2;
    }
    cnt=1;
    p=read();
    while(p--)
    {
        d=read(),n=read();
        if(n==1)
            printf("%lld 1\n",d);
        else
            printf("%lld %lld\n",d,f[n][0]<<1);
    }
    return 0;
}