#include <cstdio>
#include <set>

const int maxn=50000+5;
int n,m,sum;

struct unionFind
{
	int bin[maxn];
	
	unionFind()
	{
		for(int i=1;i<=n;i++)
			bin[i]=i;
	}
	
	int find(int x)
	{
		if(bin[x]==x)
			return x;
		return bin[x]=find(bin[x]);
	}
	
	void uni(int x,int y)
	{
		bin[find(x)]=find(y);
	}
	
	bool query(int x,int y)
	{
		return find(x)==find(y);
	}
};

int main()
{
	for(int kase=1;;kase++)
	{
		scanf("%d %d",&n,&m);
		sum=n;
		if(n==m && n==0)
			return 0;
		unionFind u;
		int x,y;
		while(m--)
		{
			scanf("%d %d",&x,&y);
			if(!u.query(x,y))
				u.uni(x,y);
		}
		std::set<int> s;
		for(int i=1;i<=n;i++)
			s.insert(u.find(i));
		printf("Case %d: %d\n",kase,s.size());
	}
}
