#include <cstdio>
#include <cctype>
#include <cstring>

typedef long long ll;

inline ll read()
{
    char c = getchar();
    ll s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline ll max(ll a,ll b)
{
	return a>b?a:b;
}

const ll maxn=1e5+5;
ll s[maxn],n,k;
ll f[maxn][2];

struct mono_queue
{
	ll q[maxn];
	int p[maxn];
	ll head,tail;
	mono_queue()
	{
		memset(q,0LL,sizeof q);
		memset(p,0,sizeof p);
		head=tail=1;
	}
	void push(ll x,int i)
	{
		while(head<=tail && q[tail]<=x)//因为后面还要加元素进去，所以这里必须head<=tail 
			tail--;
		q[++tail]=x;
		p[tail]=i;
		return;
	}
	void maintain(int i)
	{
		while(head<tail && p[head]<i-k)
			head++;
	}
	ll front(int i)
	{
		return head>tail?0:q[head];
	}
}q;

int main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]+read();
	for(int i=1;i<=n;i++)
	{
		q.maintain(i);
		f[i][0]=max(f[i-1][0],f[i-1][1]);
		f[i][1]=q.front(i)+s[i];
		//printf("%d:%lld %lld\n",i,f[i][0],f[i][1]);
		q.push(f[i][0]-s[i],i);
	}
	printf("%lld\n",max(f[n][1],f[n][0]));
	return 0;
}
