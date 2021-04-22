#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct Point{
    int x,y;
}p1[1005],p2[1005];

bool cmp1(Point a,Point b)
{
    if(a.x!=b.x)
        return a.x<b.x;
    else
        return a.y<b.y;
}
bool cmp2(Point a,Point b)
{
    if(a.x!=b.x)
        return a.x>b.x;
    else
        return a.y<b.y;
}

int main()
{
    int n,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++) {
        scanf("%d %d",&p1[i].x,&p1[i].y);p2[i].x=p1[i].x;p2[i].y=p1[i].y;}
        sort(p1,p1+n,cmp1);
        sort(p2,p2+n,cmp2);
        n--;
        bool ok=1;
        int sum=p1[0].x+p2[0].x;
        for(int i=0;i<n;i++)
        {
            if(p1[i].x+p2[i].x!=sum||p1[i].y!=p2[i].y)
            {
                printf("NO\n");
                ok=0;
                break;
            }
        }
        if(ok) printf("YES\n");
    }
    return 0;
}