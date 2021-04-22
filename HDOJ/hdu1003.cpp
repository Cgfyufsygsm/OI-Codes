#include <cstdio>
#include <cctype>

inline int read()
{
    char c = getchar();
    int s = 0, x = 1;
    while (!isdigit(c))
    {
        if(c=='-')
            x=-x;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s*x;
}

const int maxn=100000+5;
int a[maxn],f[maxn];
int n,s,t,T,ans,anss,anst;

int main()
{
    T=read();
    for(int kase=1;kase<=T;kase++)
    {
        n=read();
        for(int i=1;i<=n;i++)
            a[i]=read();
        ans=f[1]=a[1],s=t=anss=anst=1;
        for(int i=2;i<=n;i++)
        {
            if(f[i-1]+a[i]<a[i])
            {
                s=t=i;
                f[i]=a[i];
                if(a[i]>ans)
                    ans=a[i],anss=anst=i;
            }
            else
            {
                t=i;
                f[i]=f[i-1]+a[i];
                if(f[i]>ans)
                    ans=f[i],anss=s,anst=i;
            }
        }
        if(kase>1)
            printf("\n");
        printf("Case %d:\n%d %d %d\n",kase,ans,anss,anst);
    }
    return 0;
}