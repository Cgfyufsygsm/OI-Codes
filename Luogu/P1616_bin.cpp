#include <cstdio>

int t,m,f[100010],totm,w[100010],c[100010];
inline int max(int a,int b){return a>b?a:b;}

int main()
{
    scanf("%d %d", &t ,&m);
    totm=1;
    for(int i=1;i<=m;i++)
    {
        int ww, cc;
        scanf("%d %d", &cc, &ww);//cc is time, ww is value
        for(int j=0;(1<<j)*cc<=t;j++)
        {
            w[totm]=ww*(1<<j);
            c[totm++]=cc*(1<<j);
        }
    }
    for(int i=1;i<=totm;i++)
        for(int j=t;j>=c[i];j--)
            f[j]=max(f[j],f[j-c[i]]+w[i]);
    printf("%d\n",f[t]);
    return 0;
}