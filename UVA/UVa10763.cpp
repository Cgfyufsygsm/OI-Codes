#include <cstdio>
#include <cstring>
using namespace std;

int inn[1000005],out[1000005];

int main()
{
    int n;
    while(scanf("%d",&n)&&n)
    {
        memset(inn,0,sizeof(inn));
        memset(out,0,sizeof(out));
        for(int i=1;i<=n;i++)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            inn[a]++;
            out[b]++;
        }
        bool ok=1;
        for(int i=0;i<=100000;i++)
        if(inn[i]!=out[i]) {ok=0;printf("NO\n");break;}
        if(ok) printf("YES\n");
    }
    return 0;
}