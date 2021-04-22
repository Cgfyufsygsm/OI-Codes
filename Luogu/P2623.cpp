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

inline int min(int a,int b)
{
    return a<b?a:b;
}

int f[2025];

int main()
{
    int n=read(),m=read();
    for(int i=1;i<=n;++i)
    {
        int t,a,b,c;
        t=read(),a=read(),b=read();
        if(t==1)
            for(int j=m;j>=0;j--)
                for(int k=1;k<=j;k++)
                    f[j]=max(f[j],f[j-k]+a*k*k-b*k);
        else if(t==3)
            for(int j=b;j<=m;j++)
                f[j]=max(f[j],f[j-b]+a);
        else if(t==2)
        {
            c=read();
            for(int j=m;j>=b;j--)
                for(int k=1;k<=min(c,j/b);k++)
                    f[j]=max(f[j],f[j-b*k]+a*k);
        }
    }
    printf("%d\n",f[m]);
    return 0;
}