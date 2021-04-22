#include <cstdio>
#include <cctype>

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

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=2005;
int v[maxn],f[maxn][maxn];

int main()
{
    int n=read();
    for(int i=1;i<=n;i++)
        v[i]=read();
    for(int len=n-1,day=1;len>=1;len--,day++)
        for(int i=1,j=i+len-1;j<=n;i++,j++)
            f[i][j]=max(f[i][j+1]+v[j+1]*day,f[i-1][j]+v[i-1]*day);
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=max(ans,f[i][i]+n*v[i]);
    printf("%d\n",ans);
    return 0;
}