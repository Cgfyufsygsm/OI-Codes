#include <cstdio>

inline int max(int a,int b)
{
    return a>b?a:b;
}

const int maxn=205;
int n,m,f[maxn][maxn];

int main()
{
    scanf("%d %d",&m,&n);
    int mid=n/2+1;
    for(int l=1;l<=m;l++)
        for(int c=1;c<=n;c++)
        {
            scanf("%d",&f[l][c]);
            f[l][c]=max(max(f[l-1][c],f[l-1][c+1]),f[l-1][c-1])+f[l][c];
        }
    printf("%d\n",max(f[m][mid],max(f[m][mid+1],f[m][mid-1])));
    return 0;
}