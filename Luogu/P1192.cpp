//dp:f[i]=\sum_{j=i-k}^{i-1}f[j]

#include <iostream>
using namespace std;
typedef long long ll;
ll n,k;
ll f[100050];
int main()
{
	cin>>n>>k;
	for(ll i = 1;i <= k;i++)f[i]=1;
    for(ll i = 2;i <= n; i++)
    	for(ll j=i-1;j>=i-k&&j>=1;j--)
    		f[i]=(f[i]+f[j])%100003;
	cout<<f[n]%100003<<endl;
	return 0;
}
