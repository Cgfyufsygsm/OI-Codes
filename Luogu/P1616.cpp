#include <cstdio>

int t,m,f[100010],totm,w[100010],c[100010];
inline int max(int a,int b){return a>b?a:b;}

int main()
{
    scanf("%d %d",&t,&m);
    for(int i=1;i<=m;i++)
        scanf("%d %d",&c[i],&w[i]);
    for(int i=1;i<=m;i++)
        for(int j=c[i];j<=t;j++)
            f[j]=max(f[j],f[j-c[i]]+w[i]);
    printf("%d\n",f[t]);
    return 0;
}