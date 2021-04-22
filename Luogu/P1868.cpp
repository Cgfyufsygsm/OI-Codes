#include <cstdio>
#include <cctype>
#include <algorithm>

using namespace std;

const int maxn=1.5e5+5;
int n,f[maxn];

struct node
{
	int x,y,s;
}a[maxn];

inline int max(int a,int b)
{
	return a>b?a:b;
}

struct cmp
{
	bool operator()(node x,node y)
	{
		if(x.y==y.y)
			return x.x<y.x;
		return x.y<y.y;
	}
};

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d %d",&a[i].x,&a[i].y),
		++a[i].x,++a[i].y,
		a[i].s=a[i].y-a[i].x+1;
	sort(a+1,a+n+1,cmp());
	for(int i=1;i<=n;i++)
		f[i]=max(f[i-1],f[upper_bound(a+1,a+n+1,(node){0,a[i].x,0},cmp())-(a+1)]+a[i].s);
	printf("%d\n",f[n]);
	return 0;
}
