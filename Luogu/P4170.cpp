#include <cstdio>
#include <cstring>

int f[55][55];

inline int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    char s[55];
    scanf("%s",s+1);
    n=strlen(s+1);
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++)
        f[i][i]=1;
    for(int l=1;l<n;l++)
        for(int i=1,j=l+1;j<=n;i++,j++)
            if(s[i]==s[j])
                f[i][j]=min(f[i][j-1],f[i+1][j]);
            else
                for(int k=i;k<j;k++)
                    f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
    printf("%d\n",f[1][n]);
    return 0;
}