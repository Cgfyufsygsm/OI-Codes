#include <cstdio>
#include <cctype>
#define L (k<<1)
#define R (L|1)
#define M ((i+j)>>1)

const int maxn=2e5+5;

inline int max(int a,int b)
{
	return a>b?a:b;
}

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

inline void swap(int &a,int &b)
{
	int t=a;
	a=b;
	b=t;
	return;
}

struct edge
{
	int to,w,next;
}e[maxn<<1];

struct tree
{
	int sum,maxans,minans;
	bool tag;
	tree operator=(const int &x)
	{
		sum=maxans=minans=x;
		tag=0;
		return *this;
	}
	tree operator-()const
	{
		return (tree)
		{
			-(this->sum),
			-(this->minans),
			-(this->maxans),
			!(this->tag) 
		};
	}
	tree operator+(const tree &b)const
	{
		return (tree)
		{
			this->sum+b.sum,
			max(this->maxans,b.maxans),
			min(this->minans,b.minans),
			0
		};
	}
}f[maxn<<2];

int n,m;
int head[maxn],cnt;
int fa[maxn],son[maxn],top[maxn],dep[maxn],size[maxn],dfn[maxn],w[maxn],wt[maxn],times;
int to[maxn];

inline void add(int u,int v,int w,int i)
{
	e[++cnt].to=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}

void dfs1(int u,int father,int upw)
{
	fa[u]=father;
	dep[u]=dep[father]+1;
	size[u]=1;
	w[u]=upw;
	int maxson=-1;
	for(int i=head[u];i;i=e[i].next)
	{
		int &v=e[i].to;
		if(v==father)
			continue;
		dfs1(v,u,e[i].w);
		to[i]=v;
		size[u]+=size[v];
		if(size[v]>maxson)
			son[u]=v,maxson=size[v];
	}
	return;
}

void dfs2(int u,int topf)
{
	dfn[u]=++times;
	wt[dfn[u]]=w[u];
	top[u]=topf;
	if(son[u])
		dfs2(son[u],topf);
	for(int i=head[u];i;i=e[i].next)
	{
		int &v=e[i].to;
		if(v==fa[u] || v==son[u])
			continue;
		dfs2(v,v);
	}
	return;
}

void build(int i,int j,int k)
{
	if(i==j)
	{
		f[k]=wt[i];
		return;
	}
	build(i,M,L);
	build(M+1,j,R);
	f[k]=f[L]+f[R];
	return;
}

void down(int i,int j,int k)
{
	f[L]=-f[L];
	f[R]=-f[R];
	f[k].tag=0;
	return;
}

tree query(int i,int j,int k,int x,int y)
{
	if(x<=i && y>=j)
		return f[k];
	if(f[k].tag)
		down(i,j,k);
	if(y<=M)
		return query(i,M,L,x,y);
	if(x>M)
		return query(M+1,j,R,x,y);
	else return query(i,M,L,x,y)+query(M+1,j,R,x,y);
}

void neg(int i,int j,int k,int x,int y)
{
	if(x<=i && y>=j)
	{
		f[k]=-f[k];
		return;
	}
	if(f[k].tag)
		down(i,j,k);
	if(x<=M)
		neg(i,M,L,x,y);
	if(y>M)
		neg(M+1,j,R,x,y);
	f[k]=f[L]+f[R];
	return;
}

int query(int u,int v,int opt)
{
	int anssum=0,ansmax=-0x3f3f3f3f,ansmin=0x3f3f3f3f;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		tree tmp=query(1,n,1,dfn[top[u]],dfn[u]);
		anssum+=tmp.sum;
		ansmax=max(tmp.maxans,ansmax);
		ansmin=min(tmp.minans,ansmin);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	if(u!=v)
	{
		tree tmp=query(1,n,1,dfn[u]+1,dfn[v]);
		anssum+=tmp.sum;
		ansmax=max(tmp.maxans,ansmax);
		ansmin=min(tmp.minans,ansmin);
	}
	if(opt==1)
		return anssum;
	if(opt==2)
		return ansmax;
	return ansmin;
}

void neg(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])
			swap(u,v);
		neg(1,n,1,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	neg(1,n,1,dfn[u]+1,dfn[v]);
	return;
}

void change(int i,int j,int k,int x,int d)
{
	if(i==j)
	{
		f[k]=d;
		return;
	}
	if(f[k].tag)
		down(i,j,k);
	if(x<=M)
		change(i,M,L,x,d);
	else change(M+1,j,R,x,d);
	f[k]=f[L]+f[R];
	return;
}

int main()
{
	freopen("P1505_1.in","r",stdin);
	freopen("P1505.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++)
	{
		int u=read()+1,v=read()+1,w=read();
		add(u,v,w,i);
		add(v,u,w,i);
	}
	dfs1(1,0,0);
	dfs2(1,1);
	build(1,n,1);
	m=read();
	char tmp[4];
	while(m--)
	{
		scanf("%s",tmp);
		int u=read(),v=read();
		if(tmp[0]=='C')
			change(1,n,1,dfn[to[u]],v);
		else if(tmp[0]=='N')
			neg(u+1,v+1);
		else if(tmp[0]=='S')
			printf("%d\n",query(u+1,v+1,1));
		else if(tmp[1]=='A')
			printf("%d\n",query(u+1,v+1,2));
		else if(tmp[1]=='I')
			printf("%d\n",query(u+1,v+1,3));
	}
	return 0;
}
