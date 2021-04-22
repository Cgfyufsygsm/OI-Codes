#include <cstdio>
#include <cctype>
#include <queue>
#include <algorithm>
#define FOR(i,j,k) for(int i=j;i<=k;++i)
#define DEC(i,j,k) for(int i=j;i>=k;--i)
#define VEC(it,c) for(std::vector<int>::iterator it=c.begin();it!=c.end();++it)

typedef long long ll;
const ll mod=998244353,maxn=1e5+5;

inline ll read()
{
	ll s=0,x=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			x=0;
		c=getchar();
	}
	while(isdigit(c))
		s=10*s+c-'0',c=getchar();
	return x?s:-s;
}

int n,m,Q,type[maxn],pos[maxn],cal[maxn],deg[maxn];
bool vis[maxn];
ll a[maxn],val[maxn],mu=1,mul[maxn],f[maxn],add[maxn];
std::vector<int> c[maxn];
std::queue<int> q;

void dfs(int id)
{
    vis[id]=true;
    mul[id]=(type[id]==2?val[id]:1);
    VEC(it,c[id])
    {
        int i=*it;
        if(!vis[i])dfs(i);
        mul[id]=mul[id]*mul[i]%mod;
    }
    return;
}

int main()
{
    n=read();
    FOR(i,1,n)a[i]=read();
    m=read();
    FOR(i,1,m)
    {
        type[i]=read();
        if(type[i]==1)pos[i]=read(),val[i]=read();
        else if(type[i]==2)val[i]=read();
        else
        {
            int ci=read();
            while(ci--)
            {
                int tmp=read();
                c[i].push_back(tmp);
                ++deg[tmp];
            }
        }
    }
    FOR(i,1,m)
        if(!vis[i] && !deg[i])
            dfs(i);
    Q=read();
    FOR(i,1,Q)cal[i]=read();
    DEC(i,Q,1)
    {
        if(type[cal[i]]==1)
            f[cal[i]]+=mu;
        else if(type[cal[i]]==2)
            mu=mu*val[cal[i]]%mod;
        else f[cal[i]]+=mu,mu=mu*mul[cal[i]]%mod;
    }
    FOR(i,1,m)
        if(!deg[i])q.push(i);
    while(!q.empty())
    {
        int i=q.front();q.pop();
        if(type[i]==1)
            add[pos[i]]=(add[pos[i]]+f[i]*val[i])%mod;
        ll tmp=f[i];
        std::reverse(c[i].begin(),c[i].end());
        VEC(it,c[i])
        {
            int g=*it;
            if(!--deg[g])
                q.push(g);
            f[g]=(f[g]+tmp)%mod,tmp=tmp*mul[g]%mod;
        }
    }
    FOR(i,1,n)
        printf("%lld ",(a[i]*mu+add[i])%mod);
    return 0;
}