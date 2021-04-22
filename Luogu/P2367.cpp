#include <cstdio>
#include <cctype>

const int maxn=5000005;
int n,p;
int a[maxn],d[maxn];

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

int main()
{
    n=read(),p=read();
    for(int i=1;i<=n;i++)
        a[i]=read(),d[i]=a[i]-a[i-1];
    int x,y,z;
    for(int i=1;i<=p;i++)
    {
        x=read(),y=read(),z=read();
        d[x]+=z,d[y+1]-=z;
    }
    int ans=0x7fffffff;
    for(int i=1;i<=n;i++)
    {
        a[i]=a[i-1]+d[i];
        ans=ans>a[i]?a[i]:ans;
    }
    printf("%d\n",ans);
    return 0;
}
