#include <cstdio>

#define HEAD -2
#define TAIL -1
#define NONE 0

using namespace std;
int n,m;

struct list{
	int left[100010],right[100010];
	list(){
		left[1]=HEAD;
		right[1]=TAIL;
	}
	void ins(int i,int k,bool p)
	{
		if(p==1)
		{
			right[i]=right[k];
			if(right[k]!=TAIL) left[right[k]]=i;
			right[k]=i;
			left[i]=k;
		}
		else
		{
			left[i]=left[k];
			if(left[k]!=TAIL) right[left[k]]=i;
			left[k]=i;
			right[i]=k;
		}
	}
	void remove(int x)
	{
		right[left[x]]=right[x];
		left[right[x]]=left[x];
		left[x]=right[x]=NONE;
	}
}l;

int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		int k,p;
		scanf("%d %d",&k,&p);
		l.ins(i,k,p);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		l.remove(x);
	}
	int now;
	for(int i=1;i<=n;i++)
	{
		if(l.left[i]==HEAD)
		{
			now=i;
			printf("%d ",i);
			break;
		}
	}
	while(l.right[now]!=TAIL)
	{
		printf("%d ",l.right[now]);
		now=l.right[now];
	}
	return 0;
}
