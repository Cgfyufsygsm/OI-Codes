#include <cstdio>
#include <algorithm>
using namespace std;

struct stick
{
    int l,w;
}a[5005];

int f[5005];

inline bool cmp(stick a,stick b)
{
    return a.l==b.l?a.w>b.w:a.l>b.l;
}

int n;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d %d",&a[i].l,&a[i].w);
    sort(a+1,a+n+1,cmp);
    int len=1;
    f[1]=a[1].w;
    for(int i=2;i<=n;i++)
    {
        if(a[i].w>f[len])
            f[++len]=a[i].w;
        else
        {
            int p=lower_bound(f+1,f+len+1,a[i].w)-f;
            f[p]=a[i].w;
        }
    }
    printf("%d\n",len);
    return 0;
}