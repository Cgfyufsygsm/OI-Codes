#include <iostream>
typedef unsigned long long ll;
using namespace std;
ll ksm(ll a, ll b, ll p)
{
	ll ans = 1%p;
	for (; b; b>>=1)
	{
		if (b&1) ans = ans*a%p;
		a = a*a%p;
	}
	return ans%p;
}
int main()
{
    ll n;
    cin>>n;
    cout<<ksm(2,n-1,6662333)<<endl;
    return 0;
}