#include <cstdio>

const int maxn=21;
int n,a[maxn],f[maxn],nxt[maxn];
bool b[maxn][maxn];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    for(int i=1;i<n;i++)
        for(int j=i+1;j<=n;j++)
            scanf("%d",&b[i][j]);
    f[n]=a[n];
    for(int i=n-1;i>=1;i--)
    {
        for(int j=i+1;j<=n;j++)
            if(f[j]>f[i] && b[i][j])
            {
                f[i]=f[j];
                nxt[i]=j;
            }
        f[i]+=a[i];
    }
    int ans=0,st;
    for(int i=1;i<=n;i++)
        if(f[i]>ans)
            ans=f[i],st=i;
    printf("%d ",st);
    for(int i=st;nxt[i];i=nxt[i])
        printf("%d ",nxt[i]);
    printf("\n%d\n",ans);
    return 0;
}