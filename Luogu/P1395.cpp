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

const int maxn=50000+5;
int f[maxn],size[maxn],g,res,sum;
int n;
std::vector<int> G[maxn];

inline int min(int a,int b)
{
	return a<b?a:b; 
}

inline int max(int a,int b)
{
	return a>b?a:b;
}

void dfs1(int fa,int now)
{
	size[now]=1;
	f[now]=0;
	for(auto i:G[now])
	{
		if(i==fa)
			continue;
		dfs1(now,i);
		size[now]+=size[i];
		f[now]=max(f[now],size[i]);
	}
	f[now]=max(f[now],n-size[now]);
	if(f[now]<=res)
	{
		if(f[now]==res)
			g=min(g,now);
		else
			g=now,res=f[now];;		
	}
	return;
}

void dfs2(int fa,int now)
{
	size[now]=1;
	for(auto i:G[now])
	{
		if(i==fa)
			continue;
		dfs2(now,i);
		size[now]+=size[i];
	}
	return;
}

void dfs3(int fa,int now)
{
	for(auto i:G[now])
	{
		if(i==fa)
			continue;
		sum+=size[i];
		dfs3(now,i);
	}
	return;
}

int main()
{
	n=read();
	int a,b;
	for(int i=1;i<n;i++)
	{
		a=read(),b=read();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	res=0x3f3f3f3f;
	dfs1(0,1);
	memset(size,0,sizeof size);
	dfs2(0,g);
	dfs3(0,g);
	printf("%d %d\n",g,sum);
}
