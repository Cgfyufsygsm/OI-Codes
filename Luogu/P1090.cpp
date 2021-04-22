#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;

ll n;
priority_queue<ll,vector<ll>,greater<ll> >q;

int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++)
    {
        ll a;
        scanf("%lld",&a);
        q.push(a);
    }
    ll ans=0;
    while(q.size()>=2)
    {
        ll a=q.top();
        q.pop();
        ll b=q.top();
        q.pop();
        ans+=(a+b);
        q.push(a+b);
    }
    printf("%lld\n",ans);
    return 0;
}