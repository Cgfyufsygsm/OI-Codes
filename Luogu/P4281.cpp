#include <cstdio>
#include <cctype>
#include <vector>

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

const int maxn=5e5+5;
int n,m;
std::vector<int> G[maxn];
int f[maxn][31],depth[maxn],lg[maxn];

void dfs(int fa,int now)
{
	depth[now]=depth[fa]+1;
	f[now][0]=fa;
	for(int i=1;i<=30;i++)
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
	n=read(),m=read();
	int a,b,x,y,z;
	for(int i=1;i<n;i++)
	{
		a=read(),b=read();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i=2;i<=n;i++)
		lg[i]=lg[i>>1]+1;
	dfs(0,1);
	while(m--)
	{
		x=read(),y=read(),z=read();
		int l1=lca(x,y),l2=lca(x,z),l3=lca(y,z);
		int l;
		if(l1==l2)
			l=l3;
		if(l2==l3)
			l=l1;
		if(l1==l3)
			l=l2;
		printf("%d %d\n",l,depth[x]+depth[y]+depth[z]-depth[l1]-depth[l2]-depth[l3]);
	}
	return 0;
}
