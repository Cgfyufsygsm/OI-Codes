#include <cstdio>
#include <cctype>
#include <vector> 
#include <cstring>

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
	int to,w;
	edge(){}
	edge(int _to,int _w)
	{
		to=_to;
		w=_w;
	}
};

const int maxn=3015;
std::vector<edge> G[maxn];
int n,m,f[maxn][maxn],size[maxn];

void dfs(int u)
{
	if(u>n-m)
		return;
	for(auto i:G[u])
	{
		int v=i.to,w=i.w;
		dfs(v);
		size[u]+=size[v];
		for(int j=size[u];j>=0;j--)
			for(int k=0;k<=min(j,size[v]);k++)
				f[u][j]=max(f[u][j],f[u][j-k]+f[v][k]-w);
	}
	return;
}

int main()
{
	n=read(),m=read();
	memset(f,0x8f,sizeof f);
	//printf("%d\n",f[1][1]);
	for(int i=1;i<=n-m;i++)
	{
		f[i][0]=0;
		int k=read(),A,C;
		while(k--)
		{
			A=read(),C=read();
			G[i].push_back(edge(A,C));
		}
	}
	for(int i=n-m+1;i<=n;i++)
	{
		f[i][1]=read();
		f[i][0]=0;
		size[i]=1;
	}
	dfs(1);
	for(int i=m;i>=0;i--)
		if(f[1][i]>=0)
		{
			printf("%d\n",i);
			return 0;
		}
}
