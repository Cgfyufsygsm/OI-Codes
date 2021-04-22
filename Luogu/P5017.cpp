#include <cstdio>
#include <cctype>
#include <algorithm>

const int maxn=505,maxt=4e6+1005;
int n,m;
int s[maxt],t[maxt],f[maxt],maxtime;
int q[maxt],head,tail;

inline double X(int j){return (double)s[j];}
inline double Y(int j){return (double)(f[j]-t[j]+j*s[j]);}
inline double slope(int a,int b){return (Y(b)-Y(a))/(s[a]==s[b]?1e-9:X(b)-X(a));}

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

inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}

int main()
{
    n=read(),m=read();
    for(int i=1,tmp;i<=n;++i)
    {
        tmp=read();
        ++s[tmp];
        maxtime=max(tmp,maxtime);
    }
    for(int i=1;i<maxtime+m;++i)
        s[i]+=s[i-1],t[i]=t[i-1]+s[i-1];
    q[head=1]=0;
    for(int i=0;i<maxtime+m;++i)
    {
        f[i]=t[i];
        double k=i;
        if(i-m>=0)
        {
            while(head<tail && slope(q[tail-1],q[tail])>=slope(q[tail],i-m))
                --tail;
            q[++tail]=i-m;
        }
        while(head<tail && slope(q[head],q[head+1])<=k)++head;
        int j=q[head];
        if(head<=tail)
            f[i]=min(f[i],f[j]+t[i]-t[j]-(i-j)*s[j]);
    }
    int ans=0x3f3f3f3f;
    for(int i=maxtime;i<maxtime+m;++i)
        ans=min(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}