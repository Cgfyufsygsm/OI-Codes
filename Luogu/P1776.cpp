#include <cstdio>

inline int max(int a,int b)
{
    return a>b?a:b;
}

int totn,W,n,v[(int)1e5+10],w[(int)1e5+10],f[(int)4e4+10];//v is value, w is cost, m is number

int main()
{
    totn=0;
    scanf("%d %d",&n,&W);
    register int vv,ww,m;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&vv,&ww,&m);
        for(int j=1;j<=m;j<<=1)
        {
            m-=j;
            v[++totn]=vv*j,w[totn]=ww*j;
            //printf("%d ",1<<j);
        }
        if(m)
            v[++totn]=vv*m,w[totn]=ww*m;
    }
    for(int i=1;i<=totn;i++)
        for(int j=W;j>=w[i];j--)
            f[j]=max(f[j],f[j-w[i]]+v[i]);
    printf("%d\n",f[W]);
    return 0;
}