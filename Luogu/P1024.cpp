#include <cstdio>
#define EPS 0.001
using namespace std;

double a,b,c,d;

double f(double x)
{
    double ans=a*x*x*x+b*x*x+c*x+d;
    return ans;
}

void binary(double l,double r)
{
    while(r-l>EPS)
    {
        double mid=(r+l)/2;
        if(f(mid)==0)
        {
            printf("%.2lf ",mid);
            return;
        }
        if(f(r)==0)
        {
            printf("%.2lf ",r);
            return;
        }
        double ansl=f(l)*f(mid),ansr=f(mid)*f(r);
        if(ansl<0)
        {
            r=mid;
            continue;
        }
        else if(ansr<0)
        {
            l=mid;
            continue;
        }
    }
    printf("%.2lf ",l);
}

int main()
{
    scanf("%lf %lf %lf %lf",&a,&b,&c,&d);
    for(int i=-100;i<=99;i++)
    {
        if(f(i+1)==0){printf("%.2lf ",i+1.0);continue;}
        else if(f(i)*f(i+1)<0)
            binary(i,i+1.0);
    }
    return 0;
}