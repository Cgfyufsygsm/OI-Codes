#include <cstdio>
#include <algorithm>
using std::sort;

int h[10005],n;//表示[i,i+1]板子的最高高度
struct pad
{
    int y,x1,x2;
}p[105];

bool cmp(pad a,pad b)
{
    return a.y<b.y;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d %d %d",&p[i].y,&p[i].x1,&p[i].x2);
    sort(p+1,p+1+n,cmp);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int x1=p[i].x1,x2=p[i].x2,y=p[i].y;
        ans+=(y-h[x1]+y-h[x2-1]);
        for(int j=x1;j<x2;j++)
            h[j]=y;
    }
    printf("%d\n",ans);
    return 0;
}