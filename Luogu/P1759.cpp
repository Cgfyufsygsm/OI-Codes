#include <cstdio>

int n,m,v,a[105],b[105],c[105],f[205][205];
bool g[105][205][205];
int ans[105];

int main()
{
    scanf("%d %d %d",&m,&v,&n);
    for(int i=1;i<=n;i++)
        scanf("%d %d %d",a+i,b+i,c+i);
    for(int i=1;i<=n;i++)
        for(int j=m;j>=a[i];j--)
            for(int k=v;k>=b[i];k--)
                if(f[j-a[i]][k-b[i]]+c[i]>f[j][k])
                    f[j][k]=f[j-a[i]][k-b[i]]+c[i],g[i][j][k]=1;
    printf("%d\n",f[m][v]);
    int cnt=0;
    for(int i=n;i>=1;i--)
    {
        if(g[i][m][v])
        {
            ans[cnt++]=i;
            m-=a[i];
            v-=b[i];
        }
    }
    for(int i=cnt-1;i>=0;i--)
        printf("%d ",ans[i]);
    return 0;
}