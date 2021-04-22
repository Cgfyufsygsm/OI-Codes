#include <cstdio>

int n,m,v[30],p[30],f[30][30000];
inline int max(int a,int b){return a>b?a:b;}

int main()
{
    scanf("%d %d",&n, &m);
    for(int i=1;i<=m;i++)
        scanf("%d %d",&v[i], &p[i]);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            if(v[i]>j)
                f[i][j]=f[i-1][j];
            else
                f[i][j]=max(f[i-1][j],f[i-1][j-v[i]]+v[i]*p[i]);
        }
    printf("%d\n",f[m][n]);
}