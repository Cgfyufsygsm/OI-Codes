#include <cstdio>
#include <cctype>
#include <stack>
#include <queue>

using std::stack;
using std::queue;

const int maxn=1e4+5,maxm=1e5+5;

int from[maxm],to[maxm];
int head1[maxm],to1[maxm],next1[maxm],cnt1;
int head2[maxm],to2[maxm],next2[maxm],cnt2;
int dfn[maxn],low[maxn],vis[maxn],bel[maxn],ind[maxn];
int w[maxn],wt[maxn],f[maxn],ans;
int times,tot,n,m;
stack<int> s;

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

inline int max(int a,int b)
{
	return a>b?a:b;
}

inline int min(int a,int b)
{
	return a<b?a:b;
}

inline void add1(int u,int v)
{
	to1[++cnt1]=v;
	next1[cnt1]=head1[u];
	head1[u]=cnt1;
}

inline void add2(int u,int v)
{
	ind[v]++;
	to2[++cnt2]=v;
	next2[cnt2]=head2[u];
	head2[u]=cnt2;
}

void tarjan(int u)
{
	dfn[u]=low[u]=++times;
	s.push(u);
	vis[u]=1;
	for(int i=head1[u];i;i=next1[i])
	{
		int &v=to[i];
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		tot++;
		while(1)
		{
			int x=s.top();
			s.pop();
			vis[x]=0;
			wt[tot]+=w[x];
			bel[x]=tot;
			if(x==u)
				break;
		}
	}
}

void topo()
{
	queue<int> q;
	for(int i=1;i<=tot;i++)
		if(!ind[i])
			q.push(i),f[i]=wt[i],ans=f[i]>ans?f[i]:ans;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head2[u];i;i=next2[i])
		{
			int &v=to2[i];
			f[v]=max(f[v],f[u]+wt[v]);
			if(!--ind[v])
				q.push(v),ans=f[v]>ans?f[v]:ans;
		}
	}
	return;
}

int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		w[i]=read();
	for(int i=1;i<=m;i++)
		from[i]=read(),to[i]=read(),add1(from[i],to[i]);
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=m;i++)
		if(bel[from[i]]!=bel[to[i]])
			add2(bel[from[i]],bel[to[i]]);
	topo();
	printf("%d\n",ans);
	return 0;
}
