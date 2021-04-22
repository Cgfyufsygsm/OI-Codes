#include <cstdio>
#include <cstring>
#define maxn 100009
int a[maxn],b[maxn],h[maxn];

using namespace std;
int main()
{
    int ans1=0;
    memset(a,0,sizeof(a));
    memset(b,1,sizeof(b));
    memset(h,0x7ffffff,sizeof(h));
    int n=1,m=0;//n:the num of missiles, m:the num of sys
    while(scanf("%d",&a[n])!=EOF)
    {
        int l=0;
        for(int i=n-1;i>0;i--)
        {
            if(a[i]>=a[n]&&b[i]>l)
                l=b[i];
        }
        b[n]=l+1;
        if(b[n]>ans1) ans1=b[n];
        int x=0;
        for(int k=1;k<=n;k++)
        {
            if(h[k]>=a[n])
                if(x==0)
                    x=k;
                else if(h[k]<h[x])
                    x=k;
        }
        if(x==0)
        {
            m++;
            x=m;
        }
        h[x]=a[n];
        n++;
    }
    printf("%d %d\n",ans1,m);
    return 0;
}