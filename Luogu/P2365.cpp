#include <cstdio>
#include <cctype>

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

typedef long long ll;
const int maxn=5005;
ll f[maxn],t[maxn],s[maxn],n,st;
int q[maxn],head,tail;

inline double Y(int i){return (double)f[i];}
inline double X(int i){return (double)s[i];}
inline double slope(int a,int b){return (Y(a)-Y(b))/(X(a)-X(b));}

int main()
{
    head=tail=1;
    n=read(),st=read();
    for(int i=1;i<=n;++i)
        t[i]=t[i-1]+read(),s[i]=s[i-1]+read();
    for(int i=1;i<=n;++i)
    {
        double k=t[i]+st;
        while(head<tail && slope(q[head],q[head+1])<k)++head;
        f[i]=f[q[head]]+t[i]*(s[i]-s[q[head]])+st*(s[n]-s[q[head]]);
        while(head<tail && slope(q[tail-1],q[tail])>slope(q[tail-1],i))--tail;
        q[++tail]=i;
    }
    printf("%lld\n",f[n]);
    return 0;
}