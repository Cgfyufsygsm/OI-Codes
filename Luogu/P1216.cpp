#include <cstdio>
#include <vector>
using namespace std;
int tower[1050][1050];

int main()
{
	int n;
	scanf("%d",&n);
	int tmp;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			scanf("%d",&tmp);
			tower[i][j]=tmp;
		}
	}
	for(int i=n-1;i>=1;i--)
	{
		for(int j=1;j<=i;j++)
		{
			tower[i][j]+=max(tower[i+1][j],tower[i+1][j+1]);
		}
	}
	printf("%d\n",tower[1][1]);
	return 0;
}
