#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n,k,f[105][105];

struct book
{
    int w,h;
}a[205];

inline bool cmp(book a,book b)
{
    return a.h<b.h;
}

inline int abs(int x)
{
    return x>=0?x:-x;
}

int main()
{
    memset(f,0x3f,sizeof(f));
    scanf("%d %d",&n,&k);
    int m=n-k;
    for(int i=1;i<=n;i++)
        scanf("%d %d",&a[i].h,&a[i].w),f[i][1]=0;
    sort(a+1,a+n+1,cmp);
    for(int i=2;i<=n;i++)
        for(int j=1;j<i;j++)
            for(int l=2;l<=min(i,m);l++)
                f[i][l]=min(f[i][l],f[j][l-1]+abs(a[j].w-a[i].w));
    int ans=0x3f3f3f3f;
    for(int i=m;i<=n;i++)
        ans=min(ans,f[i][m]);
    printf("%d\n",ans);
    return 0;
}