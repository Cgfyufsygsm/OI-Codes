#include <cstdio>
using namespace std;

struct Uf
{
	int bin[10005];
	
	Uf()
	{
		for(int i=1;i<=10002;i++)
			bin[i]=i;
	}
	int anc(int x)
	{
		if(bin[x]==x) return x;
		bin[x]=anc(bin[x]);
		return bin[x];
	}
	void uni(int x,int y)
	{
		bin[anc(x)]=anc(y);
	}
	void ask(int x,int y)
	{
		printf("%s\n",anc(x)==anc(y)?"Y":"N");
	}
}u;

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int z,x,y;
		scanf("%d%d%d",&z,&x,&y);
		if(z==1) u.uni(x,y);
		if(z==2) u.ask(x,y);
	}
	return 0;
}
