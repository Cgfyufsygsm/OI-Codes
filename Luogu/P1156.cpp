#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

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

int d,g;

struct rubbish
{
    int t,f,h;
    bool operator<(const rubbish &b)const
    {
        return t<b.t;
    }
}a[105];

int f[101][101];

int main()
{
    d=read(),g=read();
    for(int i=1;i<=g;++i)
        a[i].t=read(),a[i].f=read(),a[i].h=read();
    std::sort(a+1,a+g+1);
    a[0].f=a[0].h=a[0].t=0;
    memset(f,-1,sizeof f);
    f[0][0]=10;
    for(int i=0;i<g;++i)
        for(int j=0;j<=d;++j)
        {
            if(f[i][j]<0)continue;
            if(j+a[i+1].h>=d && f[i][j]>=a[i+1].t-a[i].t)
            {
                printf("%d\n",a[i+1].t);
                return 0;
            }
            if(f[i][j]-a[i+1].t+a[i].t>=0)
            {
                f[i+1][j+a[i+1].h]=f[i][j]-a[i+1].t+a[i].t;
                f[i+1][j]=max(f[i+1][j],f[i][j]-a[i+1].t+a[i].t+a[i+1].f);
            }
        }
    int now=10,used=0;
    for(int i=1;i<=g;++i)
    {
        if(a[i].t-a[i-1].t>now)
            break;
        used+=a[i].t-a[i-1].t;
        now-=a[i].t-a[i-1].t;
        now+=a[i].f;
    }
    printf("%d\n",now+used);
    return 0;
}