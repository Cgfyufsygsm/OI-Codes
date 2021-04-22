#include <cstdio>

const int fx[]={1,1,2,2};
const int fy[]={2,-2,1,-1};

int n,m,ans;

bool chk(int x,int y)
{
    return x>=0 && x<=m && y>=0 && y<=n;
}

void dfs(int x,int y)
{
    if(x==m && y==n)
    {
        ans++;
        return;
    }
    for(int k=0;k<4;k++)
    {
        int xx=x+fx[k],yy=y+fy[k];
        if(chk(xx,yy))
            dfs(xx,yy);
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    dfs(0,0);
    printf("%d\n",ans);
    return 0;
}