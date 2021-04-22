#include <cstdio>
#include <cstring>

inline int max(int a,int b)
{
    return a>b?a:b;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

const int maxn=2505;
int n,m,a[maxn][maxn],f[maxn][maxn],s1[maxn][maxn],s2[maxn][maxn],ans;

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
            if(!a[i][j])
            {
                s1[i][j]=s1[i][j-1]+1;
                s2[i][j]=s2[i-1][j]+1;
            }
            if(a[i][j])
                f[i][j]=min(f[i-1][j-1],min(s1[i][j-1],s2[i-1][j]))+1;
            ans=max(ans,f[i][j]);
        }
    memset(f,0,sizeof(f));
    memset(s1,0,sizeof(s1));
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
        {
            if(!a[i][j])
                s1[i][j]=s1[i][j+1]+1;
            if(a[i][j])
                f[i][j]=min(f[i-1][j+1],min(s1[i][j+1],s2[i-1][j]))+1;
            ans=max(ans,f[i][j]);
        }
    printf("%d\n",ans);
    return 0;
}