#include <cstdio>
#include <cctype>
#include <cstring>

#define f(i,a,b) for(int i=a;i<=b;i++)

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

const int maxn=1e6+5;
int count[maxn];
int n,q,a[maxn];

struct query
{
	int l,r,x;
}b[maxn];

int bl[maxn],br[maxn];

int ans[maxn];

void sort()
{
	f(i,1,q)
		ans[b[i].l]++;
	f(i,1,n)
		ans[i]+=ans[i-1];
	f(i,1,q)
		bl[ans[b[i].l]--]=i;
	memset(ans,0,sizeof ans);
	f(i,1,q)
		ans[b[i].r]++;
	f(i,1,n)
		ans[i]+=ans[i-1];
	f(i,1,q)
		br[ans[b[i].r]--]=i;
	return;
}

int main()
{
	n=read();
	f(i,1,n)
		a[i]=read();
	q=read();
	f(i,1,q)
		b[i].l=read(),b[i].r=read(),b[i].x=read();
	sort();
	memset(ans,0,sizeof ans);
	int pl=1,pr=1;
	f(i,0,n)
	{
		if(i)count[a[i]]++;
		while(b[bl[pl]].l-1<i && pl<=q)
			pl++;
		while(b[bl[pl]].l-1==i && pl<=q)
			ans[bl[pl]]-=count[b[bl[pl]].x],pl++;
		while(b[br[pr]].r<i && pr<=q)
			pr++;
		while(b[br[pr]].r==i && pr<=q)
			ans[br[pr]]+=count[b[br[pr]].x],pr++;
	}
	f(i,1,q)
		printf("%d\n",ans[i]);
	return 0;
}
