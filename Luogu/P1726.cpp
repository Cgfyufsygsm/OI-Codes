#include <cstdio>
#include <cctype>
#include <stack>
#include <queue>

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

inline int min(int a,int b)
{
	return a<b?a:b;
}

const int maxn=5000+5,maxm=50000+5;

int n,m;
int head[maxn],next[maxm<<1],to[maxm<<1],cnt;
int dfn[maxn],low[maxn],vis[maxn],tot,times;
std::stack<int> s;
std::priority_queue<int,std::vector<int>,std::greater<int> > q[maxn];

inline void add(int u,int v)
{
	to[++cnt]=v;
	next[cnt]=head[u];
	head[u]=cnt;
}

void tarjan(int u)
{
	dfn[u]=low[u]=++times;
	s.push(u);
	vis[u]=1;
	for(int i=head[u];i;i=next[i])
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
			q[tot].push(x);
			if(x==u)
				break;
		}
	}
	return;
}

int main()
{
	n=read(),m=read();
	while(m--)
	{
		int a=read(),b=read(),t=read();
		add(a,b);
		if(t==2)
			add(b,a);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	int maxscc=0,ans,minu=0x3f3f3f3f;
	for(int i=1;i<=tot;i++)
	{
		if(q[i].size()>maxscc)
			ans=i,maxscc=q[i].size();
		else if(q[i].size()==maxscc && q[i].top()<minu)
			minu=q[i].top(),ans=i;
	}
	printf("%d\n",maxscc);
	while(q[ans].size())
	{
		printf("%d ",q[ans].top());
		q[ans].pop();
	}
	return 0;
}
