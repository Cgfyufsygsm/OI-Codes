#include <cstdio>
#define lowbit(x) (x&-x)

int n,w,f[100005];

void upd(int x,int d)
{
    for(;x<=n;x+=lowbit(x))
        f[x]+=d;
    return;
}

int sum(int x)
{
    int ans=0;
    for(;x;x-=lowbit(x))
        ans+=f[x];
    return ans;
}

int main()
{
    scanf("%d\n%d\n",&n,&w);
    char c;
    int x,y;
    while(w--)
    {
        scanf("%c %d %d\n",&c,&x,&y);
        if(c=='x')
            upd(x,y);
        else
            printf("%d\n",sum(y)-sum(x-1));
    }
    return 0;
}