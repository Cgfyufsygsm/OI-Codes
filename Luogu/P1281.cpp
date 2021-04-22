#include <cstdio>
#include <cctype>
#include <cstring>
#define s(i,j) (s[j]-s[i-1])

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

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int m,s[505],K,f[505][505];

void print(int x,int ans)
{
    if(!x)return;
    for(int i=x;i>=0;--i)
        if(!i || s(i,x)>ans)
        {
            print(i,ans);
            printf("%d %d\n",i+1,x);
            return;
        }
}

int main()
{
    m=read(),K=read();
    memset(f,63,sizeof f);
    for(int i=1;i<=m;++i)
        s[i]=s[i-1]+read(),f[1][i]=s[i];
    for(int i=2;i<=K;i++)
        for(int j=1;j<=m;j++)
            for(int k=2;k<=j;k++)
                f[i][j]=min(f[i][j],max(f[i-1][k-1],s(k,j)));
    //printf("%d\n",f[K][m]);
    print(m,f[K][m]);
    return 0;
}