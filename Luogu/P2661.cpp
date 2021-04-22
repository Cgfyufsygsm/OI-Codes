//P2661
#include <cstdio>
using namespace std;

int g[200050],t[200050];
int n;
int time,ans=1000000000;

inline void make_edge(int u,int v)
{
	g[u]=v;
}

inline void dfs(int cur)
{
	if(!g[cur]) return;
	time++;
	if(time>t[cur]&&t[cur]){
		ans=min(ans,time-t[cur]);
		t[cur]=0;
		g[cur]=0;
		return;
	}
	t[cur]=time;
	dfs(g[cur]);
	t[cur]=0;
	g[cur]=0;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int t;
		scanf("%d",&t);
		make_edge(i,t);
	}
	for(int i=1;i<=n;i++) dfs(i);
	printf("%d",ans);
	return 0;
}
