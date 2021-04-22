#include <cstdio>
#include <cstring>

const int maxn=5005;
int n;
char s[maxn];
int f[2][maxn];

inline int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    scanf("%d",&n);
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
        f[i&1][i]=0;
    for(int i=n-1;i>=1;i--)
        for(int j=i+1;j<=n;j++)
            if(s[i]==s[j])
                f[i&1][j]=f[(i+1)&1][j-1];
            else
                f[i&1][j]=min(f[(i+1)&1][j],f[i&1][j-1])+1;
    printf("%d\n",f[1][n]);
    return 0;
}