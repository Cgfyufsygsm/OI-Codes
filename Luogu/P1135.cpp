#include <cstdio>
#include <queue>
using namespace std;
struct node{
	int cur,step;
};
int n,a,b,k[205];
bool vis[205];
void bfs()
{
	queue<node> q;
	q.push((node){a,0});
	int ans=-1;
	while(!q.empty())
	{
		int cur=q.front().cur,step=q.front().step;
		if(cur==b)
		{
			ans=step;
			break;
		}
		if(cur+k[cur]<=n&&(!vis[cur+k[cur]])) 
		{
			q.push((node){cur+k[cur],step+1});
			vis[cur+k[cur]]=1;
		}
		if(cur-k[cur]>=1&&(!vis[cur-k[cur]]))
		{
			q.push((node){cur-k[cur],step+1});
			vis[cur-k[cur]]=1;
		}
		q.pop();
	}
	printf("%d\n",ans);
	return;
}
int main()
{
	scanf("%d %d %d",&n,&a,&b);
	for(int i=1;i<=n;i++) scanf("%d",&k[i]);
	bfs();
	return 0;
}
