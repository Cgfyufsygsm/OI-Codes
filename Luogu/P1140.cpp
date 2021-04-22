#include <cstdio>

int d[6][6]={
    {0,0,0,0,0,0},
    {0,5,-1,-2,-1,-3},
    {0,-1,5,-3,-2,-4},
    {0,-2,-3,5,-2,-2},
    {0,-1,-2,-2,5,-1},
    {0,-3,-4,-2,-1,0}
};


inline int max(int a,int b)
{
    return a>b?a:b;
}

inline int max(int a,int b,int c)
{
    return max(max(a,b),c);
}

int l1,l2;
char a[105],b[105];
int f[105][105];

int main()
{
    scanf("%d %s",&l1,a+1);
    scanf("%d %s",&l2,b+1);
    for(int i=1;i<=l1;i++)
    {
        a[i]=a[i]=='A'?1:a[i]=='C'?2:a[i]=='G'?3:4;
        f[i][0]=f[i-1][0]+d[a[i]][5];
    }
    for(int i=1;i<=l2;i++)
    {
        b[i]=b[i]=='A'?1:b[i]=='C'?2:b[i]=='G'?3:4;
        f[0][i]=f[0][i-1]+d[5][b[i]];
    }
    for(int i=1;i<=l1;i++)
        for(int j=1;j<=l2;j++)
            f[i][j]=max(f[i-1][j]+d[a[i]][5],f[i][j-1]+d[5][b[j]],f[i-1][j-1]+d[a[i]][b[j]]);
    printf("%d\n",f[l1][l2]);
    return 0;
}