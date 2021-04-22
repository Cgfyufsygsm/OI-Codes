#include <cstdio>
#include <cctype>

const int maxn=5e4+5;
int n;
double a[maxn],b[maxn],f[maxn],sum[maxn],L;
int q[maxn],head,tail;

inline double X(int x){return b[x];}
inline double Y(int x){return f[x]+b[x]*b[x];}
inline double slope(int a,int b){return (Y(a)-Y(b))/(X(a)-X(b));}

inline int read()
{
    bool w=0;
    int x=0;
    char c=getchar();
    while(!isdigit(c))
    {
        if(c=='-')
            w=1;
        c=getchar();
    }
    while(isdigit(c))
        x=x*10+c-'0',c=getchar();
    return w?-x:x;
}

int main()
{
    n=read(),L=read();
    for(int i=1;i<=n;++i)
    {
        sum[i]=sum[i-1]+read();
        a[i]=sum[i]+i;
        b[i]=sum[i]+i+L+1;
    }
    b[0]=sum[0]+0+L+1;
    head=tail=1;
    for(int i=1;i<=n;++i)
    {
        while(head<tail&&slope(q[head],q[head+1])<2*a[i])
            ++head;
        int j=q[head];
        f[i]=f[j]+(a[i]-b[j])*(a[i]-b[j]);
        while(head<tail && slope(i,q[tail-1])<slope(q[tail-1],q[tail]))
            --tail;
        q[++tail]=i;
    }
    printf("%lld\n",(long long)f[n]);
    return 0;
}