#include <cstdio>

int n,m,f[105][105],s[105][105],ans;
inline int maxin(int a,int b,bool c)
{
    if(c)
        return a>b?a:b;
    else
        return a<b?a:b;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&s[i][j]);
            if(s[i][j])
                f[i][j]=maxin(f[i-1][j-1],maxin(f[i-1][j],f[i][j-1],0),0)+s[i][j];
            ans=ans>f[i][j]?ans:f[i][j];
        }
    printf("%d\n",ans);
    return 0;
}