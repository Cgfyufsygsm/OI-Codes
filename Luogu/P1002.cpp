#include <cstdio>
typedef unsigned long long ull;
ull f[30][30];
bool mk[30][30];
int hx,hy,bx,by;
const int fx[8]={1,1,2,2,-1,-1,-2,-2};
const int fy[8]={2,-2,1,-1,2,-2,1,-1};

bool chk(int x,int y)
{
    return x>=1&&y>=1;
}

int main()
{
    scanf("%d %d %d %d",&bx,&by,&hx,&hy);
    bx++,by++,hx++,hy++;
    for(int k=0;k<8;k++)
    {
        int xx=hx+fx[k],yy=hy+fy[k];
        if(chk(xx,yy))
            mk[xx][yy]=1;
    }
    mk[hx][hy]=1;
    f[1][0]=1;
    for(int i=1;i<=27;i++)
        for(int j=1;j<=27;j++)
        {
            if(mk[i][j])
                continue;
            f[i][j]=f[i-1][j]+f[i][j-1];
        }
    printf("%llu\n",f[bx][by]);
    return 0;
}