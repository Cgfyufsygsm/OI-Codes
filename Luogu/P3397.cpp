#include <cstdio>
#include <cctype>

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

const int maxn=1e3+5;
int d[maxn][maxn];

int main()
{
    int n=read(),m=read();
    while(m--)
    {
        int x1=read(),y1=read(),x2=read(),y2=read();
        d[x1][y1]++;
        d[x1][y2+1]--;
        d[x2+1][y1]--;
        d[x2+1][y2+1]++;
    }
    for(int x=1;x<=n;x++)
    {
        for(int y=1;y<=n;y++)
        {
            d[x][y]+=d[x-1][y]+d[x][y-1]-d[x-1][y-1];
            printf("%d ",d[x][y]);
        }
        printf("\n");
    }
    return 0;
}