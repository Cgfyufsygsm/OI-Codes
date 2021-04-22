#include <cstdio>
#include <cstring>
#define FOR(i,a,b) for(int i=a;i<=b;i++)

inline int max(int a,int b)
{
    return a>b?a:b;
}

int n,cnt;
int f[500];

struct cube
{
    int h,x,y;
    bool operator<(const cube b)const
    {
        return ((x<b.x && y<b.y)||(x<b.y && y<b.x));
    }
}a[500];

int dp(int i)
{
    if(f[i])
        return f[i];
    f[i]=a[i].h;
    FOR(j,1,cnt)
        if(a[j]<a[i])
            f[i]=max(f[i],dp(j)+a[i].h);
    return f[i];
}

int main()
{
    int kase;
    while(scanf("%d",&n)==1 && n)
    {
        cnt=0;
        FOR(i,1,n)
        {
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            a[++cnt]=(cube){x,y,z};
            a[++cnt]=(cube){y,x,z};
            a[++cnt]=(cube){z,x,y};
        }
        memset(f,0,sizeof f);
        int ans=0;
        FOR(i,1,cnt)
            ans=max(ans,dp(i));
        printf("Case %d: maximum height = %d\n",++kase,ans);
    }
    return 0;
}