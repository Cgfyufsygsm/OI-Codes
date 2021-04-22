#include <cstdio>
#include <cctype>

#define ind(x) 

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
    {
        if(c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int max(int a,int b)
{
    return a>b?a:b;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

const int maxn=1e6+5;
int n,a[maxn<<1];
int minl=1e7,maxr; 

int main()
{
    n=read();
    int l,r;
    while(n--)
    {
        l=read(),r=read();
        a[(l<<1)-1]++,a[(r<<1)]--;
        minl=min(minl,l);
        maxr=max(maxr,r);
    }
    for(int i=(minl<<1)-1;i<=(maxr<<1);i++)
        a[i]+=a[i-1];
    //for(int i=(minl<<1)-1;i<=(maxr<<1);i++)
     //   printf("%d ",a[i]);
    int curl=minl,curr=minl,flag=1;
    for(int i=(minl<<1)-1;i<=(maxr<<1);i++)
    {
        if(flag==1)
        {
            if(!a[i])
            {
                printf("%d %d\n",curl,curr);
                curl=curr=0;
                flag=0;
            }
            else if(a[i] && i&1)
                curr=(i+1)>>1;
        }
        else
            if(a[i])
            {
                curl=curr=(i+1)>>1;
                flag=1;
            }
        if(i>=maxr<<1)
            return 0;
    }
    return 0;
}