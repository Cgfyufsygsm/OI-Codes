#include <cstdio>
#include <cstring>
#define f(i,a,b) for(int i=a;i<=b;++i)

const int maxn=1e6+5;
int n,m,r[maxn],d[maxn],s[maxn],t[maxn],diff[maxn];

inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}

bool check(int mid)
{
    memset(diff,0,sizeof(diff));
    f(i,1,mid)
        diff[s[i]]+=d[i],diff[t[i]+1]-=d[i];
    int ans=0;
    f(i,1,n)
    {
        ans+=diff[i];
        if(ans>r[i])
            return 0;
    }
    return 1;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
#endif
    n=read(),m=read();
    f(i,1,n)
        r[i]=read();
    f(i,1,m)
        d[i]=read(),s[i]=read(),t[i]=read();
    int l=1,r=m,ans;
    while(l<r)//mid越大越难不挨卡
    {
        int mid=l+r>>1;
        //printf("l:%d,r:%d,mid:%d\n",l,r,mid);
        if(check(mid))
            l=mid+1;
        else
            r=mid;
    }
    if(r!=m)
        printf("-1\n%d\n",r);
    else
        printf("0\n");
    return 0;
}