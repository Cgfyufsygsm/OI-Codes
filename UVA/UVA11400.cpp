#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

inline int read()
{
    bool w=0;
    int x=0;
    char c=getchar();
    while(!isdigit(c))
    {
        if(c=='-')
            w=1;
        c=getchar();
    }
    while(isdigit(c))
        x=x*10+c-'0',c=getchar();
    return w?-x:x;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

int n;

struct lamp
{
    int v,k,c,l;
    bool operator<(const lamp &b)const
    {
        return v<b.v;
    }
}a[1005];

int s[1005];
int f[1005];

int main()
{
    while(n=read())
    {
        for(int i=1;i<=n;i++)
            a[i].v=read(),a[i].k=read(),a[i].c=read(),a[i].l=read();
        std::sort(a+1,a+n+1);
        for(int i=1;i<=n;i++)
            s[i]=s[i-1]+a[i].l;
        memset(f,63,sizeof f);
        f[0]=0;
        for(int i=1;i<=n;i++)
            for(int j=0;j<i;j++)
                f[i]=min(f[i],f[j]+(s[i]-s[j])*a[i].c+a[i].k);
        printf("%d\n",f[n]);
    }
    return 0;
}