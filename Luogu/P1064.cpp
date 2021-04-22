#include <cstdio>
#include <algorithm>
using std::max;

int f[32010],v[70][3],p[70][3],aux[70],n,m;

int main()
{
    scanf("%d %d",&n,&m);
    int _v,_p,q;
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d %d",&_v,&_p,&q);
        if(!q)
            v[i][0]=_v,p[i][0]=_p;
        else
            v[q][++aux[q]]=_v,p[q][aux[q]]=_p;
    }
    for(int i=1;i<=m;i++)
        for(int j=n;j>=v[i][0];j--)
        {
            auto cost=[i](int x){return v[i][0]+v[i][x];};
            auto cost3=[i](){return v[i][0]+v[i][1]+v[i][2];};
            auto pdc=[i](int x){return v[i][x]*p[i][x];};
            f[j]=max(f[j],f[j-v[i][0]]+pdc(0));
            if(j>=cost(1))
                f[j]=max(f[j],f[j-cost(1)]+pdc(0)+pdc(1));
            if(j>=cost(2))
                f[j]=max(f[j],f[j-cost(2)]+pdc(0)+pdc(2));
            if(j>=cost3())
                f[j]=max(f[j],f[j-cost3()]+pdc(0)+pdc(1)+pdc(2));
        }
    printf("%d\n",f[n]);
    return 0;
}