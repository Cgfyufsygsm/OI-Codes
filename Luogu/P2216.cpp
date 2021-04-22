#include <cstdio>
#include <cctype>
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

inline int max(int a,int b)
{
	return a>b?a:b;
}

inline int min(int a,int b)
{
	return a<b?a:b;
}

const int maxm=1005,maxn=105;
int n,a,b,m[maxm][maxm];
int ans=0x7fffffff;

struct mono_queue_max
{
	int head,tail;
	int p[maxm],q[maxm];
	void clear()
	{
		memset(p,0,sizeof p);
		memset(q,0,sizeof q);
		head=1,tail=0;
		return;
	}
	void maintain(int i)
	{
		while(head<=tail && p[head]<=i-n)
			head++;
		return;
	}
	void push(int x,int i)
	{
		maintain(i);
		while(head<=tail && q[tail]<=x)
			tail--;
		q[++tail]=x;
		p[tail]=i;
		return;
	}
	int front(int i)
	{
		maintain(i);
		return q[head];
	}
	mono_queue_max()
	{
		clear();
	}
}ql_max[maxm],qc_max[maxm];

struct mono_queue_min
{
	int head=1,tail=0;
	int p[maxm],q[maxm];
	void clear()
	{
		memset(p,0,sizeof p);
		memset(q,0,sizeof q);
		head=1,tail=0;
		return;
	}
	void maintain(int i)
	{
		while(head<=tail && p[head]<=i-n)
			head++;
		return;
	}
	void push(int x,int i)
	{
		maintain(i);
		while(head<=tail && q[tail]>=x)
			tail--;
		q[++tail]=x;
		p[tail]=i;
		return;
	}
	int front(int i)
	{
		maintain(i);
		return q[head];
	}
	mono_queue_min()
	{
		clear();
	}
}ql_min[maxm],qc_min[maxm];

int main()
{
	a=read(),b=read(),n=read();
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
			m[i][j]=read();
	for(int i=1;i<n;i++)
		for(int j=1;j<=b;j++)
		{
			qc_min[j].push(m[i][j],i);
			qc_max[j].push(m[i][j],i);
		}
	for(int i=1;i+n-1<=a;i++)
	{
		for(int j=1;j<=b;j++)
		{
			qc_min[j].push(m[i+n-1][j],i+n-1);
			qc_max[j].push(m[i+n-1][j],i+n-1);
		}
		for(int j=1;j<n;j++)
		{
			ql_min[i].push(m[i][j],j);
			ql_max[i].push(m[i][j],j);
		}
		for(int j=1;j+n-1<=b;j++)
		{
			ql_min[i].push(m[i][j+n-1],j+n-1);
			ql_max[i].push(m[i][j+n-1],j+n-1);
			int curmax=ql_max[i].front(i),curmin=ql_min[i].front(i);
			for(int k=0;k<n;k++)
			{
				curmax=max(qc_max[j+k].front(j+k),curmax);
				curmin=min(qc_min[j+k].front(j+k),curmin);
			}
			ans=min(ans,curmax-curmin);
		}
	}
	printf("%d\n",ans);
	return 0;
}
