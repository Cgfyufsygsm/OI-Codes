#include <cstdio>
#include <cctype>
#include <cstring>

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

const int maxn=1e3+5;
int n,p,s,maxw,minw=2e9,f[maxn];

struct file
{
    int w,v;
}a[maxn];

bool chk(int mid)
{
    memset(f,0,sizeof f);
    int ret=0;
    for(int i=1;i<=n;i++)
        for(int j=s;j>=a[i].w;j--)
            if(a[i].w<=mid)
                f[j]=max(f[j],f[j-a[i].w]+a[i].v),ret=max(ret,f[j]);
    return ret>=p;
}

int main()
{
    n=read(),p=read(),s=read();
    for(int i=1;i<=n;++i)
        a[i].w=read(),a[i].v=read(),maxw=max(maxw,a[i].w),minw=min(minw,a[i].w);
    int l=minw,r=maxw,mid,ans;
    while(l<=r)
    {
        mid=l+r>>1;
        //printf("%d %d %d\n",l,r,mid);
        if(chk(mid))
            ans=mid,r=mid-1;
        else l=mid+1;
    }
    if(ans>0) printf("%d\n",ans);
    else printf("No Solution!\n");
    return 0;
}