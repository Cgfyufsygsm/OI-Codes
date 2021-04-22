#include <cstdio>
#include <cctype>

const int maxn=1e6+5;
int n,a[maxn];

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

inline void swap(int &x,int &y)
{
    int c=x;
    x=y;
    y=c;
    return;
}

void qsort(int l,int r)
{
    int i=l,j=r,k=a[l];
    if(i>=j)
        return;
    while(i<j)
    {
        while(i<j && a[j]>=k)
            --j;
        while(i<j && a[i]<=k)
            ++i;
        swap(a[i],a[j]);
    }
    swap(a[l],a[i]);
    qsort(l,i-1);
    qsort(i+1,r);
}

int main()
{
    n=read();
    for(register int i=1;i<=n;i++)
        a[i]=read();
    qsort(1,n);
    for(register int i=1;i<=n;i++)
        printf("%d ",a[i]);
    return 0;
}