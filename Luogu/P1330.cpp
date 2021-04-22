//P1330
#include <cstdio>
#include <vector>
using namespace std;
const int N=1e5+10;
vector<int> G[N];
void addedge(int u,int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

bool vis[N];
bool color[N];
int c[2];
int n,m;

bool dfs(int cur, bool col)
{
	if(vis[cur]){
		if(color[cur]==col)
			return true;
		else 
			return false;
	}
	vis[cur]=1;
	c[color[cur]=col]++;
	bool flag=1;
	for(int i=0;i<G[cur].size();i++)
	{
		int v=G[cur][i];
		flag=flag&&dfs(v,!col);
	}
	return flag;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	int ans=0;
	for(int i=1;i<=n;i++)//从第一个点开始遍历处理连通图 
	{
		c[1]=c[0]=0;
		if(vis[i]) continue;//如果已处理，跳过
		if(!dfs(i,0))
		{
			puts("Impossible\n");
			return 0;
		}
		ans+=min(c[1],c[0]);
	}
	printf("%d\n",ans);
	return 0;
}
