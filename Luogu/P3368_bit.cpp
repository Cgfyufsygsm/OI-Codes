#include <cstdio>
#define lowbit(x) (x&-x)
const int maxn=5e5+5;

int a[maxn],d[maxn],c[maxn],n,m;//a为原序列，d为差分序列，c为d建的树状数组

void upd(int x,int k)
{
    while(x<=n) c[x]+=k,x+=lowbit(x);
    return;
}

void build()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        d[i]=a[i]-a[i-1];
        upd(i,d[i]);
    }
    //for(int i=1;i<=n;i++) printf("%d ",d[i]);
    //for(int i=1;i<=n;i++) printf("%d ",c[i]);
    return;
}

int query(int x)
{
    int ans=0;
    for(;x>0;x-=lowbit(x))ans+=c[x];
    return ans;
}

int main()
{
    build();
    for(int i=1;i<=m;i++)
    {
        int c,x,y,k;
        scanf("%d %d",&c,&x);
        if(c==1)
        {
            scanf("%d %d",&y,&k);
            upd(x,k);
            upd(y+1,-k);
        }
        if(c==2) printf("%d\n",query(x));
    }
    return 0;
}