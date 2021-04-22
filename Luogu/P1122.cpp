#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>

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

const int maxn=16000+5;
int n,w[maxn];
std::vector<int> G[maxn];
int f[maxn][2],fa[maxn],ans;

void dfs(int u,int father)
{
	f[u][0]=w[u];
	fa[u]=father;
	for(auto v:G[u])
	{
		if(v==father)
			continue;
		dfs(v,u);
		f[u][0]=max(f[u][0],f[u][0]+f[v][0]);
	}
	ans=max(ans,f[u][0]);
	return;
}

int main()
{
	memset(f,0x8f,sizeof f);
	n=read();
	for(int i=1;i<=n;i++)
		w[i]=read();
	for(int i=1;i<n;i++)
	{
		int a=read(),b=read();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
