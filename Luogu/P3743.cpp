#include <cstdio>
#include <cctype>

const double EPS=1e-6;
const int maxn=100000+5;

int p,n,a[maxn],b[maxn];

bool chk(double mid)
{
    double needed;
    for(int i=1;i<=n;i++)
        if(b[i]<mid*a[i])
            needed+=(mid*a[i]-b[i]);
    return mid*p>=needed;
}

char tmp[100];

int main()
{
    scanf("%d %d",&n,&p);
    double suma=0;
    for(int i=1;i<=n;++i)
        scanf("%d%d",a+i,b+i),suma+=a[i];
    if(p>=suma)
    {
        printf("-1\n");
        return 0;
    }
    double ans;
    for(double l=0,r=1e10;r-l>=EPS;)
    {
        double mid=(l+r)/2.0;
        sprintf(tmp,"%lf\n",mid);
        if(chk(mid))ans=mid,l=mid;
        else r=mid;
    }
    printf("%.10lf\n",ans);
    return 0;
}