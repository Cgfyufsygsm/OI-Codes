//GZ-0025 杨涛瑜 
#include <cstdio>
#include <cctype>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define DEC(i,a,b) for(int i=a;i>=b;--i)

typedef unsigned long long ll;

inline int read()
{
	int s=0;
	bool x=0;
	char c=getchar();
	while(!isdigit(c))
		x|=(c=='-'),c=getchar();
	while(isdigit(c))
		s=10*s+c-'0',c=getchar();
	return x?-s:s;
}

inline void swap(ll &a,ll &b)
{
	ll t=a;
	a=b;
	b=t;
}

const int maxn=1e5+5;
const int maxm=5*maxn;

ll gcd(ll a,ll b)
{
	if(a<b)swap(a,b);
	if(!b)return a;
	return gcd(b,a%b);
}

inline ll lcm(ll a,ll b)
{
	return a/gcd(a,b)*b;
}

int head[maxn],to[maxm],nxt[maxm],n,m,cnt;
int oud[maxn],ind[maxn];

inline void add(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

struct frac
{
	ll up,down;
	frac(){
		up=0,down=1;
	}
	frac operator+(const frac &b)const
	{
		ll _lcm=lcm(this->down,b.down);
		frac ret;
		ret.down=_lcm;
		ret.up=up*(_lcm/down)+b.up*(_lcm/b.down);
		ll _gcd=gcd(ret.up,ret.down);
		if(_gcd)ret.up/=_gcd,ret.down/=_gcd;
		return ret;
	}
	frac operator/(const ll &div)const
	{
		frac ret;
		ret.up=this->up,ret.down=this->down*div;
		return ret;
	}
}f[maxn];

int q[maxn],qhead=1,qtail=0;

int main()
{
	n=read(),m=read();
	FOR(i,1,n)
	{
		oud[i]=read();
		f[i].up=0ll,f[i].down=1ll;
		FOR(j,1,oud[i])
		{
			int to=read();
			add(i,to);++ind[to];
		}
	}
	FOR(i,1,n)
		if(!ind[i])
			q[++qtail]=i,f[i].up=1ll;
	while(qhead<=qtail)
	{
		int u=q[qhead++];
		frac add;
		if(oud[u])add=f[u]/oud[u];
		for(int i=head[u];i;i=nxt[i])
		{
			int &v=to[i];
			f[v]=f[v]+add;
			if(!--ind[v])
				q[++qtail]=v;
		}
	}
	for(int i=1;i<=n;++i)
		if(!oud[i])
			printf("%lld %lld\n",f[i].up,f[i].down);
	return 0;
}