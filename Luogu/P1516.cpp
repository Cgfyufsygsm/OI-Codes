#include <cstdio>

typedef long long ll;
ll X,Y,M,N,L,gcd;

void exgcd(ll &x,ll &y,ll a,ll b)
{
	if(!b)
		x=1,y=0,gcd=a;
	else
		exgcd(y,x,b,a%b),y-=a/b*x;
}

int main()
{
	scanf("%lld %lld %lld %lld %lld",&X,&Y,&M,&N,&L);
	ll x,y;
	ll a=M-N,c=Y-X,&b=L;
	if(a<0)
		a=-a,c=-c ;
	exgcd(x,y,a,b);
	if(c%gcd)
	{
		printf("Impossible\n");
		return 0;
	}
	printf("%lld\n",(x%(b/gcd)*c/gcd+b/gcd)%(b/gcd));
	return 0;
}
