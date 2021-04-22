#include <cstdio>
#include <vector>

const int maxn=1505;
int n,f[maxn][2];
std::vector<int> G[maxn];

inline int min(int a,int b)
{
	return a<b?a:b;
}

void dfs(int fa,int now)
{
	f[now][0]=0,f[now][1]=1;
	for(auto i:G[now])
	{
		if(i!=fa)
		{
			dfs(now,i);
			f[now][0]+=f[i][1];
			f[now][1]+=min(f[i][0],f[i][1]);
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int index,k,r;
		scanf("%d %d",&index,&k);
		while(k--)
		{
			scanf("%d",&r);
			G[index].push_back(r);
		}
	}
	dfs(-1,0);
	printf("%d",min(f[0][0],f[0][1]));
	return 0;
}
