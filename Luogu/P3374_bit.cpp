#include <cstdio>
#define lowbit(x) (x&(-x))
//算出x二进制的从右往左出现第一个1以及这个1之后的那些0组成数的二进制对应的十进制的数

const int maxn=5e5+5;

int a[maxn],c[maxn],n,m;

void build();
void add(int,int);
int query(int i,int j);

void build()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        add(i,a[i]);
    }
}

void add(int x,int k)
{
    while(x<=n) c[x]+=k,x+=lowbit(x);
}

int query(int x)
{
    int ans=0;
    for(;x;x-=lowbit(x)) ans+=c[x];
    return ans;
}

int uni(int x,int y)
{
    return query(y)-query(x-1);
}

int main()
{
    build();
    for(int i=1;i<=m;i++)
    {
        int c,x,y;
        scanf("%d %d %d",&c,&x,&y);
        if(c==1) add(x,y);
        if(c==2) printf("%d\n",uni(x,y));
    }
    return 0;
}