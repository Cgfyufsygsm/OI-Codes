#include <cstdio>
#include <cctype>

const int maxn=1e6+5;
int n,a[maxn],b[maxn];

int read()
{
    char c=getchar();
    int s=0,p=1;
    while(!isdigit(c))
    {
        if(c=='-')
            p=-p;
        c=getchar();
    }
    while(isdigit(c))
        s=10*s+c-'0',c=getchar();
    return s*p;
}

void msort(int l,int r)
{
    if(l>=r)
        return;
    int mid=l+r>>1;
    msort(l,mid);
    msort(mid+1,r);
    int i=l,j=mid+1,cnt=l;
    while(i<=mid && j<=r)
    {
        if(a[i]<=a[j])
            b[cnt++]=a[i++];
        if(a[i]>a[j])
            b[cnt++]=a[j++];
    }
    while(i<=mid)
        b[cnt++]=a[i++];
    while(j<=r)
        b[cnt++]=a[j++];
    for(i=l;i<=r;i++)
        a[i]=b[i];
}

int main()
{
    n=read();
    for(register int i=1;i<=n;i++)
        a[i]=read();
    msort(1,n);
    for(register int i=1;i<=n;i++)
        printf("%d ",a[i]);
    return 0;
}