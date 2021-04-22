#include <cstdio>
#include <cctype>
#include <cstring>

inline int min(int a,int b)
{
	return a<b?a:b;
}

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
    {
        if(c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn=160;

int n,p;
int next[maxn<<1],to[maxn<<1],head[maxn<<1],cnt;

int size[maxn],f[maxn][maxn];

inline void add(int u,int v)
{
	to[++cnt]=v;
	next[cnt]=head[u];
	head[u]=cnt;
}

void dfs1(int u,int fa)
{
	size[u]=1;
	f[u][1]=0;
	for(int i=head[u];i;i=next[i])
	{
		int &v=to[i];
		if(v==fa)
			continue;
		f[u][1]++;
		dfs1(v,u);
		size[u]+=size[v];
	}
}

void dfs2(int u,int fa)
{
	for(int i=head[u];i;i=next[i])
	{
		int &v=to[i];
		if(v==fa)
			continue;
		dfs2(v,u);
		for(int j=size[u];j>=0;j--)
			for(int k=1;k<j;k++)
				f[u][j]=min(f[u][j],f[u][j-k]+f[v][k]-1);
	}
	return;
}

int main()
{
	memset(f,0x3f,sizeof f);
	n=read(),p=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	dfs2(1,0);
	int ans=f[1][p];
	for(int i=2;i<=n;i++)
		ans=min(ans,f[i][p]+1);
	printf("%d\n",ans);
	return 0;
}
