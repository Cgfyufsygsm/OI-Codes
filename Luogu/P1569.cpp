#include <cstdio>
#include <cctype>
#define sum(l,r) (s[r]-s[l-1])

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

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=1005;
int a[maxn],n,s[maxn]; 
int f[maxn];
//f[i] 到第i头牛为最后一组的最后一个，最多的分组个数

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read(),s[i]=s[i-1]+a[i];
    f[1]=a[1]>0?1:0;
    for(int i=2;i<=n;i++)
        for(int j=1;j<=i;j++)
            if(sum(j,i)>=0 && (j>1 && f[j-1]>0))
                f[i]=max(f[i],f[j-1]+1);
    if(f[n]>0)
        printf("%d\n",f[n]);
    else
        printf("Impossible\n");
    return 0;
}