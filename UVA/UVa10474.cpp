#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 10005

int main()
{
    int kase=0;
    for(;;)
    {
        int N,Q;
        scanf("%d %d",&N,&Q);
        if(!N||!Q) break;
        int a[maxn];
        printf("CASE# %d:\n",++kase);
        for(int i=0;i<N;i++) scanf("%d",&a[i]);
        sort(a,a+N);
        while(Q--)
        {
            int x;
            scanf("%d",&x);
            int p=lower_bound(a,a+N,x)-a;
            if(a[p]==x) printf("%d found at %d\n",x,p+1);
            else printf("%d not found\n",x);
        }
    }
    return 0;
}