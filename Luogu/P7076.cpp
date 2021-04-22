#include <cstdio>
#include <cctype>
#define FOR(i,j,k) for(int i=j;i<=k;++i)

typedef unsigned long long ll;
const int maxn=1e6+5,maxc=1e8+5;

inline ll read()
{
	ll s=0;
	char c=getchar();
	while(!isdigit(c))
		c=getchar();
	while(isdigit(c))
		s=10*s+c-'0',c=getchar();
	return s;
}

ll n,m,c,k,a[maxn],p[maxn],q[maxn];
bool vis[maxc],affected[65];
ll tmp=0;

int main()
{
	n=read(),m=read(),c=read(),k=read()-1;
	FOR(i,1,n)
		a[i]=read(),tmp|=a[i];
	FOR(i,1,m)
	{
		p[i]=read(),q[i]=read();
		if(tmp&(1ull<<p[i]))
			vis[q[i]]=1;
	}
	FOR(i,1,m)
	{
		if(!(tmp&(1ull<<p[i])))
			if(!vis[q[i]])
				affected[p[i]]=1;
	}
	ll nafed=0;
	if(k==63 && n==0)
    {
        printf("18446744073709551616");
        return 0;
    }
	FOR(i,0,k)
		if(!affected[i])
			++nafed;
	printf("%llu\n",(1ull<<nafed)-n);
	return 0;
}