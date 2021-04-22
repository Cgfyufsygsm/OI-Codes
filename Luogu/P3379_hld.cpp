#include <cstdio>
#include <cctype>
#include <vector>

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline void swap(int &a,int &b)
{
	int t=b;
	b=a;
	a=t;
	return;
}

const int maxn=500000+5;
int n,m,s;
int dep[maxn],fa[maxn],size[maxn],son[maxn],top[maxn];
std::vector<int> G[maxn];

void dfs1(int x,int father,int d)
{
	dep[x]=d;
	fa[x]=father;
	size[x]=1;
	int maxson=-1;
	for(auto y:G[x])
	{
		if(y==father)
			continue;
		dfs1(y,x,d+1);
		size[x]+=size[y];
		if(size[y]>maxson)
			son[x]=y,maxson=size[y];
	}
	return;
}

void dfs2(int x,int topf)
{
	top[x]=topf;
	if(!son[x])
		return;
	dfs2(son[x],topf);
	for(auto y:G[x])
	{
		if(y==fa[x] || y==son[x])
			continue;
		dfs2(y,y);
	}
	return;
}

int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])
		return x;
	else return y;
}

int main()
{
	n=read(),m=read(),s=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs1(s,0,1);
	dfs2(s,s);
	while(m--)
	{
		int a=read(),b=read();
		printf("%d\n",lca(a,b));
	}
	return 0;
}
