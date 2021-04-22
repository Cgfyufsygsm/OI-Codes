#include <cstdio>
#include <vector>

int n,m,s;
const int maxn=500000+5;
std::vector<int> G[maxn];
int f[maxn][31],lg[maxn],depth[maxn];

void dfs(int fa,int now)
{
	f[now][0]=fa;
	depth[now]=depth[fa]+1;
	for(int i=1;i<=25;i++)
		f[now][i]=f[f[now][i-1]][i-1];
	for(auto i:G[now])
		if(i!=fa)
			dfs(now,i);
	return; 
}

int lca(int x,int y)
{
	if(depth[x]<depth[y])
	{
		int t=y;
		y=x;
		x=t;
	}
	while(depth[x]>depth[y])
		x=f[x][lg[depth[x]-depth[y]]];
	if(x==y)
		return x;
	for(int k=lg[depth[x]];k>=0;k--)
		if(f[x][k]!=f[y][k])
			x=f[x][k],y=f[y][k];
	return f[x][0];
}

int main()
{
	scanf("%d %d %d",&n,&m,&s);
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i = 2; i <= n; ++i)
	  lg[i] = lg[i/2]+1;
	dfs(0,s);
	while(m--)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		printf("%d\n",lca(a,b));
	}
	return 0;
}
