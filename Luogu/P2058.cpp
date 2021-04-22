#include <cstdio>
#include <queue>
using std::queue;

const int maxn=3e5+5;
struct node
{
    int t,s;
};
queue<node> q;
int n,w[maxn];

int main()
{
    scanf("%d",&n);
    int t,k,x,ans=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&t,&k);
        while(!q.empty())
        {
            if(q.front().t<=t-86400)
            {
                if(!--w[q.front().s])
                    ans--;
                q.pop();
            }
            else
                break;
        }
        while(k--)
        {
            scanf("%d",&x);
            q.push((node){t,x});
            if(!(w[x]++))
                ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}