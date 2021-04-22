#include <cstdio>

typedef long long ll;
ll n,a[15],m[15],Mul,M[16],inv[16],x,y;

void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0)
	{
		x=1;y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}

int main()
{
	Mul=1;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld %lld",m+i,a+i);
		Mul*=m[i];
	}
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		M[i]=Mul/m[i];
		x=0,y=0;
		exgcd(M[i],m[i],x,y);
		inv[i]=x<0?x+m[i]:x;
		ans+=a[i]*M[i]*inv[i];
	}
	printf("%lld\n",ans%Mul);
	return 0;
}
