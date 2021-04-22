#include <cstdio>
#define lowbit(x) (x&-x)

const int maxn=1e5+5;
int n,m;
int t[maxn];

void add(int x,int d)
{
    while(x<=n)
    {
        t[x]+=d;
        x+=lowbit(x);
    }
    return;
}

bool query(int x)
{
    int ans=0;
    while(x)
    {
        ans+=t[x];
        x-=lowbit(x);
    }
    return ans&1;
}

int main()
{
    //freopen("1.out","w",stdout);
    scanf("%d %d",&n,&m);
    int c,x,y;
    while(m--)
    {
        scanf("%d %d",&c,&x);
        if(c==1)
        {
            scanf("%d",&y);
            add(x,1);
            add(y+1,-1);
        }
        else
            printf("%d\n",query(x));
    }
    return 0;
}