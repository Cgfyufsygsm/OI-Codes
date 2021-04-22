#include <cstdio>
#define max(a,b) (a>b?a:b)

int T,n,totn,f[1010],t[100010],c[100010];

int main()
{
    int teh,tem,tsh,tsm;
    scanf("%d:%d %d:%d %d",&tsh,&tsm,&teh,&tem,&n);
    T=(teh-tsh)*60+tem-tsm;
    int tt,cc,a;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&tt,&cc,&a);
        if(!a)
            a=999999;
        int cnt=0;
        for(int j=1;j<=a && cnt<=T;j<<=1)
        {
            cnt+=j;
            a-=j;
            t[++totn]=tt*j,c[totn]=cc*j;
        }
        if(a && cnt<=T)
            t[++totn]=tt*a,c[totn]=cc*a;
    }
    for(int i=1;i<=totn;i++)
        for(int j=T;j>=t[i];j--)
            f[j]=max(f[j],f[j-t[i]]+c[i]);
    printf("%d\n",f[T]);
    return 0;
}