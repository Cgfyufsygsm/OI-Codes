#include <cstdio>
#include <cctype>
#include <cstring>

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

int n,t,p[105][105],f[10005];

int main()
{
    t=read(),n=read();
    int m=read();
    for(int i=1;i<=t;i++)
        for(int j=1;j<=n;j++)
            p[i][j]=read();
    int ans=m;
    for(int i=1;i<t;i++)
    {
        memset(f,~0x3f,sizeof(f));
        f[ans]=ans;
        for(int j=1;j<=n;j++)
            for(int k=ans;k>=p[i][j];k--)
                f[k-p[i][j]]=max(f[k-p[i][j]],f[k]+p[i+1][j]-p[i][j]);
        int maxn=0;
        for(int j=0;j<=ans;j++)
            maxn=max(maxn,f[j]);
        ans=maxn;
    }
    printf("%d\n",ans);
    return 0;
}