#include <cstdio>
#include <cctype>
#include <vector>

inline int read()
{
    char c = getchar();
    int s = 0, x = 1;
    while (!isdigit(c))
    {
    	if(c=='-')
    		x = -x;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s*x;
}

inline int max(int a,int b)
{
	return a>b?a:b;
}

inline int min(int a,int b)
{
	return a<b?a:b;
}

struct edge
{
	int from,to,w;
	edge(){}
	edge(int a,int b,int c)
	{
		from=a;
		to=b;
		w=c;
	}
};

const int maxn=105;
int n,q;
std::vector<edge> G[maxn];
int f[maxn][maxn],ans,size[maxn];

void dfs(int u,int fa)
{
	for(auto e:G[u])
	{
		size[u]++;
		if(e.to==fa)
			continue;
		int v=e.to,w=e.w;
		dfs(v,u);
		size[u]+=size[v];
		for(int j=min(q,size[u]);j>=1;j--)
			for(int k=0;k<j;k++)
				f[u][j]=max(f[u][j],f[u][j-k-1]+f[v][k]+w);
	}
}

int main()
{
	n=read(),q=read();
	for(int i=1;i<n;i++)
	{
		int from=read(),to=read(),w=read();
		G[from].push_back(edge(from,to,w));
		G[to].push_back(edge(to,from,w));
	}
	dfs(1,0);
	printf("%d\n",f[1][q]);
	return 0;
}
