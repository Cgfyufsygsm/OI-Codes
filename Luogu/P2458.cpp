#include <cstdio>
#include <vector>

const int maxn=1e5+5;
std::vector<int> G[maxn];
int n,k[maxn],f[maxn][3],vis[maxn];

inline int min(int a,int b)
{
	return a<b?a:b;
}

void dfs(int fa,int now)
{
	f[now][0]=k[now];
	f[now][1]=f[now][2]=0;//1 is controlled by its father, 2 is controlled by its son
	bool flag=0;
	int minans=0x3f3f3f3f;
	for(auto i:G[now])
	{
		if(i==fa)
			continue;
		dfs(now,i);
		f[now][0]+=min(min(f[i][1],f[i][2]),f[i][0]);
		f[now][1]+=min(f[i][0],f[i][2]);
		f[now][2]+=min(f[i][0],f[i][2]);
		if(f[i][0]<f[i][2])
			flag=1;
		minans=min(minans,f[i][0]-f[i][2]);
	}
	if(!flag)
		f[now][2]+=minans;
	return;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int idx,kk,m,r;
		scanf("%d%d%d",&idx,&kk,&m);
		k[idx]=kk;
		while(m--)
		{
			scanf("%d",&r);
			vis[r]++;
			G[idx].push_back(r);
			G[r].push_back(idx);
		}
	}
	int root;
	for(int i=1;i<=n;i++)
		if(!vis[i])
			root=i;
	dfs(0,root);
	printf("%d\n",min(f[root][0],f[root][2]));
	return 0;
}
