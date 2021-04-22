#include <cstdio>
#include <cstring>

int n,k;
double l[10000+5];
char tmp[1000];

bool chk(double mid)
{
    int tot;
    for(int i=1;i<=n;++i)
        tot+=(int)(l[i]/mid);
    return tot>=k;
}

int main()
{
    scanf("%d %d",&n,&k);
    double sum=0;
    for(int i=1;i<=n;++i)
        scanf("%lf",l+i),sum+=l[i];
    double l=0,r=sum,mid,ans;
    while(r-l>=1e-5)
    {
        mid=(l+r)/2;
        //sprintf(tmp,"%lf %lf %lf\n",l,r,mid);
        if(chk(mid))
            l=mid+1e-5,ans=mid;
        else
            r=mid-1e-5;
    }
    sprintf(tmp,"%.3lf",ans);
    tmp[strlen(tmp)-1]='\0';
    printf("%s\n",tmp);
    return 0;
}