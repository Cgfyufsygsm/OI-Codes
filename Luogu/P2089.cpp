#include <cstdio>
using namespace std;
int total=0,n=0;
bool flag=false;
int a[10],ans[10000000],l=0;
void print()
{
	for(int i=0;i<10;i++)
	{
		ans[l]=a[i];
		l++;
	}
	return;
}
void dfs(int step,int sum)
{
	if(step==10)
	{
		if(sum==n)
		{
			flag=true;
			total++;
			print();
		}
		return;
	}
	if(sum>n)
		return;
	a[step]=1;
	dfs(step+1,sum+1);
	a[step]=2;
	dfs(step+1,sum+2);
	a[step]=3;
	dfs(step+1,sum+3);
	a[step]=0;
	return;
}
int main()
{
	scanf("%d",&n);
	dfs(0,0);
	if(flag)
	{
		printf("%d\n",total);
		int j=0;
		for(int i=0;i<l;i++)
		{
			j++;
			printf("%d ",ans[i]);
			if(j%10==0)
				printf("\n");
		}
	}
	else
		printf("0");
	return 0;
}
