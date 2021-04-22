#include <cstdio>
#include <cctype>
#include <vector>

typedef long long ll;

inline ll read()
{
    char c = getchar();
    ll s = 0, x = 1;
    while (!isdigit(c))
    {
    	if(c=='-')
    		x = -x;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s*x;
}

inline ll max(ll a,ll b)
{
	return a>b?a:b;
}

struct edge
{
	ll from,to,w;
	edge(){}
	edge(ll a,ll b,ll c)
	{
		from=a;
		to=b;
		w=c;
	}
};

const int maxn=500000+5;
ll n,s;
std::vector<edge> G[maxn];
ll f[maxn],maxt[maxn];

void dfs(ll u,ll fa)
{
	for(auto e:G[u])
	{
		if(e.to==fa)
			continue;
		ll v=e.to,t=e.w;
		dfs(v,u);
		f[u]+=f[v];
		maxt[u]=max(maxt[u],t+maxt[v]);
	}
	for(auto e:G[u])
	{
		if(e.to==fa)
			continue;
		ll v=e.to;
		f[u]+=maxt[u]-maxt[v]-e.w;
	}
	return;
}

int main()
{
	n=read(),s=read();
	for(int i=1;i<n;i++)
	{
		ll a=read(),b=read(),t=read();
		G[a].push_back(edge(a,b,t));
		G[b].push_back(edge(b,a,t));
	}
	dfs(s,0);
	printf("%lld\n",f[s]);
	return 0;
}
