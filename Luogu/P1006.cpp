#include <cstdio>
#include <algorithm>
using std::max;

int m,n,map[501][501],f[501][501];

int main()
{
    scanf("%d %d",&m,&n);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&map[i][j]);
    for(int k=3;k<=n+m;k++)
        for(int i=m;i>=1;i--)
            for(int j=m;j>i;j--)
                f[i][j]=max(max(f[i][j],f[i-1][j-1]),max(f[i][j-1],f[i-1][j])),
                f[i][j]+=map[i][k-i]+map[j][k-j];
    printf("%d\n",f[m-1][m]);
    return 0;
}