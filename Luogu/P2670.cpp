#include <cstdio>

int n,m,f[105][105];
const int inf=0x3f3f3f3f;
const int fx[8]={1,1,1,-1,-1,-1,0,0};
const int fy[8]={0,1,-1,0,1,-1,1,-1};

int main()
{
    scanf("%d %d\n",&n,&m);
    char tmp;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            tmp=getchar();
            if(tmp=='*')
            {
                f[i][j]=inf<<1;
                for(int k=0;k<8;k++)
                {
                    int xx=i+fx[k],yy=j+fy[k];
                    f[xx][yy]++;
                }
            }
        }
        getchar();
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(f[i][j]<=inf)
                printf("%d",f[i][j]);
            else
                printf("*");
        }
        printf("\n");
    }
    return 0;
}