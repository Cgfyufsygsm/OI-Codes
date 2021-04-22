#include <cstdio>
#include <cctype>
#include <vector>
#define L (k<<1)
#define R (L|1)
#define M (i+j>>1)

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

const int maxn=1e5+5;
int n,m,r,p,w[maxn],wt[maxn];
int id[maxn],dep[maxn],fa[maxn],son[maxn],size[maxn],top[maxn];
int cnt;
int f[maxn<<2],tag[maxn<<2];
std::vector<int> G[maxn];

void build(int i,int j,int k)
{
	if(i==j)
	{
		f[k]=wt[i];
		if(f[k]>p)
			f[k]%=p;
		return;
	}
	build(i,M,L);
	build(M+1,j,R);
	f[k]=(f[L]+f[R])%p;
}

void down(int i,int j,int k)
{
	f[L]=(f[L]+tag[k]*(M-i+1)%p)%p;
	f[R]=(f[R]+tag[k]*(j-M)%p)%p;
	tag[L]+=tag[k],tag[R]+=tag[k];
	tag[k]=0;
}

void modify(int i,int j,int x,int y,int k,int d)
{
	if(x<=i && y>=j)
	{
		f[k]=(f[k]+d*(j-i+1)%p)%p;
		tag[k]+=d;
		return;
	}
	if(tag[k])
		down(i,j,k);
	if(x<=M)
		modify(i,M,x,y,L,d);
	if(y>M)
		modify(M+1,j,x,y,R,d);
	f[k]=(f[L]+f[R])%p;
}

int query(int i,int j,int x,int y,int k)
{
	if(x<=i && y>=j)
		return f[k];
	if(tag[k])
		down(i,j,k);
	int ans=0;
	if(x<=M)
		ans=(ans+query(i,M,x,y,L))%p;
	if(y>M)
		ans=(ans+query(M+1,j,x,y,R))%p;
	return ans;
}

int query_range(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		ans=(ans+query(1,n,id[top[x]],id[x],1))%p;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	ans=(ans+query(1,n,id[x],id[y],1))%p;
	return ans;
}

int query_son(int x)
{
	return query(1,n,id[x],id[x]+size[x]-1,1)%p;
}

void modify_range(int x,int y,int z)
{
	z%=p;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		modify(1,n,id[top[x]],id[x],1,z);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	modify(1,n,id[x],id[y],1,z);
	return;
}

void modify_son(int x,int z)
{
	modify(1,n,id[x],id[x]+size[x]-1,1,z);
	return;
}

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
			maxson=size[y],son[x]=y;
	}
}

void dfs2(int x,int topf)
{
	id[x]=++cnt;
	wt[cnt]=w[x];
	top[x]=topf;
	if(!son[x])
		return;
	dfs2(son[x],topf);
	for(auto y:G[x])
	{
		if(y==son[x] || y==fa[x])
			continue;
		dfs2(y,y);
	}
}

int main()
{
	n=read(),m=read(),r=read(),p=read();
	for(int i=1;i<=n;i++)
		w[i]=read();
	for(int i=1;i<n;i++)
	{
		int a=read(),b=read();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs1(r,0,1);
	dfs2(r,r);
	build(1,n,1);
	while(m--)
	{
		int opt=read(),x=read(),y,z;
		if(opt==1)
		{
			y=read(),z=read();
			modify_range(x,y,z);
		}
		else if(opt==2)
		{
			y=read();
			printf("%d\n",query_range(x,y));
		}
		else if(opt==3)
		{
			z=read();
			modify_son(x,z);
		}
		else
			printf("%d\n",query_son(x));
	}
	return 0;
}
