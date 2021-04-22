#include <cstdio>
using namespace std;

struct unionFind{
	
	int bin[100005];
	
	unionFind(){
		for(int i=1;i<=100002;i++)
			bin[i]=i;
	}
	int anc(int x){
		if(bin[x]==x) return x;
		return anc(bin[x]);
	}
	void uni(int x,int y)
	{
		bin[anc(x)]=anc(y);
	}
	void ask(int x,int y)
	{
		printf("%s\n",anc(x)==anc(y)?"Yes":"No");
	}
};

unionFind u;

int main()
{
	int n,m,p;
	scanf("%d%d%d",&n,&m,&p);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		u.uni(x,y);
	}
	while(p--){
		int x,y;
		scanf("%d%d",&x,&y);
		u.ask(x,y);
	}
	return 0;
}
