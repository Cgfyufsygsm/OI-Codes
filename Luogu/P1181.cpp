#include<iostream>
using namespace std;
typedef long long ll;
int main()
{
    ll n,lim,buck=0;
    cin>>n>>lim;
    ll cnt=0;
    for(ll i=1;i<=n;i++)
    {
        ll tmp;
        cin>>tmp;
        if(tmp+buck>lim)
        {
            buck=0;
            cnt++;
        }
        buck+=tmp;
    }
    cout<<cnt+1<<endl;
    return 0;
}