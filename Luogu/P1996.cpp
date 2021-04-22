#include <cstdio>
#include <queue>
using namespace std;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	queue<int> q;
	for(int i=1;i<=n;i++)
		q.push(i);
	for(int i=1;!q.empty();i++)
	{
		int x=q.front();
		q.pop();
		if(i%m)
		{
			q.push(x);
		}
		else
		{
			printf("%d ",x);
		}
	}
	return 0;
}
