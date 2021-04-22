#include <cstdio>

const int maxn=355,maxg=41;
int n,m,g[5],a[maxn],f[maxg][maxg][maxg][maxg];

inline int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    register int x;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&x);
        g[x]++;
    }
    f[0][0][0][0]=a[1];
    for(int i=0;i<=g[1];i++)
        for(int j=0;j<=g[2];j++)
            for(int k=0;k<=g[3];k++)
                for(int l=0;l<=g[4];l++)
                {
                    int r=i+j*2+k*3+l*4+1;
                    if(i)
                        f[i][j][k][l]=max(f[i][j][k][l],f[i-1][j][k][l]+a[r]);
                    if(j)
                        f[i][j][k][l]=max(f[i][j][k][l],f[i][j-1][k][l]+a[r]);
                    if(k)
                        f[i][j][k][l]=max(f[i][j][k][l],f[i][j][k-1][l]+a[r]);
                    if(l)
                        f[i][j][k][l]=max(f[i][j][k][l],f[i][j][k][l-1]+a[r]);
                }
    printf("%d\n",f[g[1]][g[2]][g[3]][g[4]]);
    return 0;
}