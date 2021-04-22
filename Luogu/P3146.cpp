#include <cstdio>

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=248+10;
int f[maxn][maxn],n;

int main()
{
    scanf("%d",&n);
    int ans=0;
    for(int i=1;i<=n;i++)
        scanf("%d",&f[i][i]),ans=max(ans,f[i][i]);
    for(int len=2;len<=n;len++)
        for(int i=1,j=i+len-1;j<=n;i++,j++)
            for(int k=i;k<j;k++)
            {
                if(f[i][k]==f[k+1][j] && f[i][k] && f[k+1][j])
                    f[i][j]=f[i][k]+1;
                ans=max(ans,f[i][j]);
            }
    printf("%d\n",ans);
    return 0;
}