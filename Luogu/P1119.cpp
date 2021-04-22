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

inline int min(int a,int b)
{
    return a<b?a:b;
}

const int maxn=205;
int n,m,t[maxn],f[maxn][maxn],q;

inline void floyd(int k)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
    return;
}

int main()
{
    n=read(),m=read();
    memset(f,0x3f,sizeof(f));
    for(int i=0;i<n;i++)
        t[i]=read(),f[i][i]=0;
    while(m--)
    {
        int x=read(),y=read(),w=read();
        f[x][y]=f[y][x]=w;
    }
    q=read();
    int now=0;
    while(q--)
    {
        int x=read(),y=read(),s=read();
        while(t[now]<=s && now<n)
            floyd(now++);
        if(t[x]>s || t[y]>s || f[x][y]>=0x3f3f3f3f)
            printf("-1\n");
        else
            printf("%d\n",f[x][y]);
    }
    return 0;
}