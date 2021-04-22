#include <cstdio>

int f[1005],t,m,w[105],c[105];
inline int max(int x,int y){return x>y?x:y;}

int main()
{
    scanf("%d %d",&t,&m);
    for(int i=1;i<=m;i++)
        scanf("%d %d",&w[i],&c[i]);
    for(int i=1;i<=m;i++)
        for(int j=t;j>=w[i];j--)
            f[j]=max(f[j-w[i]]+c[i],f[j]);
    printf("%d\n",f[t]);
    return 0;
}