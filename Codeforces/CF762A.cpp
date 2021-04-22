#include <cstdio>
#include <queue>
typedef long long ll;

ll n,k,ans;
std::priority_queue<ll,std::vector<ll>,std::greater<ll> > q;

int main()
{
    scanf("%lld %lld",&n,&k);
    for(ll i=1;i*i<=n;i++)
    {
        if(n%i==0)
        {
            //printf("%d %d\n",i,n/i);
            q.push(i);
            if(n/i!=i)q.push(n/i);
        }
    }
    if(q.size()<k) ans=-1;
    else
    {
        for(ll i=1;i<k;i++)
            q.pop();
        ans=q.top();
    }
    printf("%lld\n",ans);
    return 0;
}