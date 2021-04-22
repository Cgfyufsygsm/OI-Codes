#include <cstdio>
#include <cctype>
#include <cstring>

#define W(i,j) (w[j]-w[i-1])

typedef long long ll;

template<typename T> T min(T a,T b)
{
    return a<b?a:b;
}

inline ll read()
{
    ll s=0;
    char c=getchar();
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=s*10+c-'0',c=getchar();
    return s;
}

const int maxn=1005;
ll w[maxn],s[22][maxn<<1];
double f[maxn];
ll lg[maxn];

inline ll mins(int i,int j)
{
    int t=lg[j-i+1];
    return min(s[t][i],s[t][j-(1<<t)+1]);
}

signed main()
{
    ll maxw=read(),l=read()*60,n=read();
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        w[i]=w[i-1]+read(),
        s[0][i]=read(),
        lg[i]=lg[i/2]+1;
    //printf("debug");
    for(int j=1;j<=10;j++)
        for(int i=1;i<=n;i++)
            s[j][i]=min(s[j-1][i],s[j-1][i+(1ll<<(j-1))]);
    //printf("debug2");
    for(int i=1;i<=n;i++)
    {
        f[i]=(double)l/s[0][i]+f[i-1];
        for(int j=i-1;j>=1;j--)
            if(W(j,i)<=maxw)
                f[i]=min(f[i],f[j-1]+(double)l/mins(j,i));
            else
                break;
    }
    printf("%.1f\n",f[n]);
    return 0;
}