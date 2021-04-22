#include <cstdio>

int n,M,T,m[105],t[105];
int f[205][205];

inline int max(int _a,int _b)
{
    return _a>_b?_a:_b;
}

int main()
{
    scanf("%d %d %d",&n,&M,&T);
    for(int i=1;i<=n;i++)
        scanf("%d %d",m+i,t+i);
    for(int i=1;i<=n;i++)
        for(int j=M;j>=m[i];j--)
            for(int k=T;k>=t[i];k--)
                f[j][k]=max(f[j][k],f[j-m[i]][k-t[i]]+1);
    printf("%d\n",f[M][T]);
    return 0;
}