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
	return ans;
}
int main()
{
    ll b,p,k;
    cin>>b>>p>>k;
    cout<<b<<'^'<<p<<" mod "<<k<<'='<<ksm(b,p,k)<<endl;
    return 0;
}