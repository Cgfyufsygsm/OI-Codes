#include <cstdio>
#include <cctype>

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
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

inline int min(int a,int b)
{
    return a<b?a:b;
}

const int maxn=1e5+10;
int f[17][maxn],log[maxn];

int main()
{
    int n,m;
    n=read(),m=read();
    log[0]=-1;
    for(int i=1;i<=n;i++)
        f[0][i]=read(),
        log[i]=log[i>>1]+1;
    for(int j=1;j<17;j++)
        for(int i=1;i<=n;i++)
            f[j][i]=min(f[j-1][i],f[j-1][i+(1<<(j-1))]);
    while(m--)
    {
        int l=read(),r=read();
        int s=log[r-l+1];
        printf("%d ",min(f[s][l],f[s][r-(1<<s)+1]));
    }
    return 0;
}