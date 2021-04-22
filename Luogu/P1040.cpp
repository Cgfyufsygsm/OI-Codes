#include <cstdio>
#include <cstring>
typedef long long ll;

ll n,f[32][32],root[32][32];

ll search(int l,int r)
{
    ll now;
    if(l>r)
        return 1;
    if(f[l][r]==-1)
        for(int k=l;k<=r;k++)
        {
            now=search(l,k-1)*search(k+1,r)+f[k][k];
            if(now>f[l][r])
                f[l][r]=now,root[l][r]=k;
        }
    return f[l][r];
}

void preorder(int l,int r)
{
    if(l>r)
        return;
    int k=root[l][r];
    printf("%d ",k);
    preorder(l,k-1);
    preorder(k+1,r);
    return;
}

int main()
{
    scanf("%lld",&n);
    memset(f,-1,sizeof(f));
    for(int i=1;i<=n;i++)
        scanf("%lld",&f[i][i]),root[i][i]=i;
    printf("%lld\n",search(1,n));
    preorder(1,n);
    return 0;
}