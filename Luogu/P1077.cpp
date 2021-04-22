#include <cstdio>

const int p=1000007;
int n,m,f[105],w[1005];

inline int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    scanf("%d %d",&n,&m);
    int x;
    for(int i=1;i<=n;i++)
        scanf("%d",w+i);
    f[0]=1;
    for(int i=1;i<=n;i++)
        for(int j=m;j>=0;j--)
            for(int k=1;k<=min(w[i],j);k++)
                f[j]=(f[j]%p+f[j-k]%p)%p;
    printf("%d\n",f[m]);
    return 0;
}