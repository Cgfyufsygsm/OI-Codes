#include <cstdio>
#include <cctype>

inline int max(int a,int b)
{
	return a>b?a:b;
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

const int maxn=200000+5,mod=10007;

struct edge
{
	int v,w,next;
}e[maxn<<1];

int n,w[maxn],head[maxn],cnt,sum;
int lg[maxn];
int fa[maxn][3],f[maxn][2],ans;

inline void add(int u,int v)
{
	e[++cnt].v=v;
	e[cnt].w=1;
	e[cnt].next=head[u];
	head[u]=cnt;
}

void dfs(int u,int father,int d)
{
	fa[u][0]=father;
	for(int i=1;i<=2;i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	if(fa[u][1])
		ans=max(ans,w[u]*w[fa[u][1]]),
		sum=(sum+w[u]*w[fa[u][1]]*2)%mod;
	long long cursum=0,sqsum=0;
	int maxson=0,cimaxson=0,son=0;
	for(int i=head[u];i;i=e[i].next)
	{
		int &v=e[i].v;
		if(v==father)
			continue;
		dfs(v,u,d+1);
		son++;
		sqsum+=w[v]*w[v];
		cursum+=w[v];
		if(w[v]>maxson)
		{
			cimaxson=maxson;
			maxson=w[v];
		}
		else if(w[v]>cimaxson)
			cimaxson=w[v];
	}
	if(son>=2)
		ans=max(ans,maxson*cimaxson),
		sum=(sum+cursum*cursum%mod-sqsum%mod)%mod;;
	return;
}

int main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)
		w[i]=read();
	lg[1]=0;
	for(int i=2;i<=n;i++)
		lg[i]=lg[i/2]+1;
	dfs(1,0,1);
	printf("%d %d\n",ans,sum%mod);
	return 0;
}
