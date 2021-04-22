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

int c[2005][2005];
int f[2005][2005];

int main()
{
    int t=read(),k=read();
    c[0][0]=c[1][1]=c[1][0]=1;
    for(int i=1;i<=2000;++i)
        c[i][0]=1;
    for(int i=2;i<=2000;i++)
    {
        for(int j=1;j<=i;j++)
        {
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%k;
            f[i][j]=f[i-1][j]+f[i][j-1]-f[i-1][j-1]+(c[i][j]==0);
        }
        f[i][i+1]=f[i][i];
    }
    while(t--)
    {
        int n=read(),m=read();
        printf("%d\n",f[n][m>n?n:m]);
    }
    return 0;
}