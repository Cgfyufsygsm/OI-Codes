#include <cstdio>

typedef long long ll;
const int maxn=3e6+5;
ll n,p;
ll inv[maxn]={0,1};

int main()
{
	scanf("%lld %lld",&n,&p);
	for(ll i=2;i<=n;i++)
		inv[i]=(p-p/i)*inv[p%i]%p;
	for(int i=1;i<=n;i++)
		printf("%lld\n",inv[i]);
	return 0;
}
