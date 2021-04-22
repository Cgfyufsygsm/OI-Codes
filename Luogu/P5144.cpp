#include <cstdio>
#include <cctype>

inline int read()
{
    int s=0;
    char c=getchar();
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=s*10+c-'0',c=getchar();
    return s;
}

template<typename T>inline T max(T a,T b){return a>b?a:b;}
template<typename T>inline T min(T a,T b){return a<b?a:b;}

const int maxn=1005,maxm=105;
int n,m,sum[maxn],f[maxn][maxm];

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;++i)
        f[i][1]=sum[i]=sum[i-1]^read();
    for(int i=1;i<=n;++i)
        for(int k=2;k<=min(i,m);++k)
            for(int j=k-1;j<i;++j)
                f[i][k]=max(f[i][k],f[j][k-1]+(sum[j]^sum[i]));
    printf("%d\n",f[n][m]);
    return 0;
}