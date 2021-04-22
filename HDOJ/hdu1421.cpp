#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

const int maxn=2e3+5;
int n,k;
int w[maxn];
int f[maxn][maxn];


inline int val(int l,int r)
{
    return (w[l]-w[r])*(w[l]-w[r]);
}

int main()
{
    while(~scanf("%d %d",&n,&k))
    {
        for(int i=1;i<=n;i++)
            w[i]=read();
        std::sort(w+1,w+n+1);
        memset(f,0x3f,sizeof f);
        for(int i=0;i<=n;i++)
            f[i][0]=0;
        for(int i=2;i<=n;i++)
            for(int j=1;j<<1<=i;j++)
                f[i][j]=std::min(f[i-1][j],f[i-2][j-1]+val(i-1,i));
        printf("%d\n",f[n][k]);
    }
    return 0;
}