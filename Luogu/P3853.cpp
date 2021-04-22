#include <cstdio>
#include <cctype>

inline int max(int a,int b){return a>b?a:b;}

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

const int maxn=100000+5;
int l,n,k,a[maxn];
int maxinit;

bool chk(int mid)
{
    int used=0;
    for(int i=2;i<=n;i++)
    {
        int dist=a[i]-a[i-1];
        used+=dist/mid;
        if(dist%mid==0)--used;
    }
    return used<=k;
}

int main()
{
    l=read(),n=read(),k=read();
    for(int i=1;i<=n;++i)
    {
        a[i]=read();
        if(i>1)maxinit=max(maxinit,a[i]-a[i-1]);
    }
    int l=0,r=maxinit,mid,ans;
    while(l<=r)
    {
        //printf("l,r:%d %d\n",l,r);
        mid=l+r>>1;
        if(chk(mid))
            ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}