#include <cstdio>
#include <cstring>

const int maxv=305,maxn=2005;
int n,m,v,e;
int c[maxn],d[maxn];
double k[maxn],f[maxn][maxn][2];
int dis[maxv][maxv];

template<typename T>inline T min(T a,T b){return a<b?a:b;}

int main()
{
    scanf("%d %d %d %d",&n,&m,&v,&e);
    for(int i=1;i<=n;++i)
        scanf("%d",c+i);
    for(int i=1;i<=n;++i)
        scanf("%d",d+i);
    for(int i=1;i<=n;++i)
        scanf("%lf",k+i);
    memset(dis,0x3f,sizeof dis);
    while(e--)
    {
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        dis[a][b]=dis[b][a]=min(dis[a][b],w);
    }
    for(int i=1;i<=v;++i)
        dis[i][i]=0;
    for(int r=1;r<=v;r++)
        for(int p=1;p<=v;p++)
            for(int q=1;q<=v;q++)
                dis[p][q]=min(dis[p][q],dis[p][r]+dis[r][q]);
    memset(f,127,sizeof f);
    f[1][0][0]=f[1][1][1]=0;
    for(int i=2;i<=n;++i)
    {
        f[i][0][0]=f[i-1][0][0]+dis[c[i-1]][c[i]];
        for(int j=1;j<=m;++j)
        {
            f[i][j][0]=min(f[i-1][j][0]+dis[c[i-1]][c[i]],
                            f[i-1][j][1]+dis[d[i-1]][c[i]]*k[i-1]+dis[c[i-1]][c[i]]*(1-k[i-1]));
            if(j)
                f[i][j][1]=min(f[i-1][j-1][0]+dis[c[i-1]][c[i]]*(1-k[i])+dis[c[i-1]][d[i]]*k[i],
                                f[i-1][j-1][1]+
                                dis[c[i-1]][c[i]]*(1-k[i-1])*(1-k[i])+
                                dis[c[i-1]][d[i]]*(1-k[i-1])*k[i]+
                                dis[d[i-1]][c[i]]*k[i-1]*(1-k[i])+
                                dis[d[i-1]][d[i]]*k[i-1]*k[i]);
        }
    }
    double ans=1e18;
    for(int i=0;i<=m;i++)
        ans=min(ans,min(f[n][i][0],f[n][i][1]));
    printf("%.2lf\n",ans);
    return 0;
}