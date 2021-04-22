#include <cstdio>

int f[20005],v,n,p[35];
inline int max(int a,int b){return a>b?a:b;}

int main()
{
    scanf("%d\n%d",&v,&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i]);
    for(int i=1;i<=n;i++)
        for(int j=v;j>=p[i];j--)
            f[j]=max(f[j],f[j-p[i]]+p[i]);
    printf("%d\n",v-f[v]);
    return 0;
}