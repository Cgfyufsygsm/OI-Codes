#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
#include <algorithm>

template<typename T>
inline T min(T a,T b)
{
    return a<b?a:b;
}

const int maxn=1005;

struct Point
{
    double x,y;
    bool operator<(const Point &b)const
    {
        return x<b.x;
    }
}p[maxn];

inline double dist(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double f[maxn][maxn];
int n;

int main()
{
    scanf("%d",&n);
    memset(f,127,sizeof f);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&p[i].x,&p[i].y);
    std::sort(p+1,p+n+1);
    for(int i=n-2;i>=1;i--)
        f[n-1][i]=dist(p[n-1],p[n])+dist(p[n],p[i]);
    for(int i=n-2;i>=1;i--)
        for(int j=1;j<i;j++)
        {
            f[i][j]=f[i+1][j]+dist(p[i],p[i+1]);
            f[i][j]=min(f[i][j],f[i+1][i]+dist(p[j],p[i+1]));
        }
    printf("%.2lf\n",f[2][1]+dist(p[1],p[2]));
    return 0;
}