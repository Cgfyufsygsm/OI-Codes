#include <cstdio>
#include <cctype>

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
    {
        if(c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int max(int a,int b)
{
    return a>b?a:b;
}

inline int abs(int x)
{
    return x>=0?x:-x;
}

const int maxn=105;
int n,a[maxn],ans,f[maxn][maxn];

inline int val(int l,int r)
{
    if(l>r)
        return 0;
    if(l==r)
        return a[l];
    return abs(a[l]-a[r])*(r-l+1);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    ans=val(1,n);
    for(int len=n-1;len>=1;len--)
        for(int i=1;i+len-1<=n;i++)
        {
            int j=i+len-1;
            for(int k=1;k<i;k++)
                f[i][j]=max(f[i][j],f[k][j]+val(k,i-1));
            for(int k=j+1;k<=n;k++)
                f[i][j]=max(f[i][j],f[i][k]+val(j+1,k));
            //printf("f[%d][%d]:%d\n",i,j,f[i][j]);
            ans=max(ans,f[i][j]+val(i,j));
        }
    printf("%d\n",ans);
    return 0;
}