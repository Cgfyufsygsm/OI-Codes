#include <cstdio>
#include <cctype>
#include <vector>

const int maxn=105;
int n,w[maxn],size[maxn],f[maxn],wsum,g,ans=0x3f3f3f3f;
std::vector<int> G[maxn];

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a,int b)
{
	return a>b?a:b;
}

void dfs1(int u,int fa)
{
	size[u]=w[u];
	for(auto v:G[u])
	{
		if(v==fa)
			continue;
		dfs1(v,u);
		size[u]+=size[v];
		f[u]=max(f[u],size[v]);
	}
	f[u]=max(f[u],wsum-f[u]);
	if(f[u]<ans)
	{
		ans=f[u];
		g=u;
	}
	return;
}

void dfs2(int u,int fa,int d)
{
	//printf("now %d,depth:%d\n",u,d);
	for(auto v:G[u])
	{
		if(v==fa)
			continue;
		dfs2(v,u,d+1);
	}
	ans+=d*w[u];
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		w[i]=read();
		wsum+=w[i];
		int l=read(),r=read();
		if(l)
			G[l].push_back(i),G[i].push_back(l);
		if(r)
			G[r].push_back(i),G[i].push_back(r);
	}
	dfs1(1,0);
	ans=0;
	dfs2(g,0,0);
	printf("%d\n",ans);
	return 0;
}
