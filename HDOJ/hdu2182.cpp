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

int t,n,a,b,k,val[105],ans;
int f[105][105];

int main()
{
    t=read();
    while(t--)
    {
        n=read(),a=read(),b=read(),k=read(),ans=0;
        for(int i=0;i<n;i++)
            val[i]=read();
        memset(f,-0x3f,sizeof f);
        f[0][0]=val[0];
        for(int i=1;i<n;i++)
            for(int j=a;j<=b && j<=i;j++)
                for(int k=1;k<i;k++)
                    f[i][k]=max(f[i][k],f[i-j][k-1]+val[i]),ans=max(ans,f[i][k]);
        printf("%d\n",ans);
    }
    return 0;
}