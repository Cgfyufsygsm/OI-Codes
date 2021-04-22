#include <cstdio>
#include <cctype>
#include <queue>
#include <cstring>

const int maxn=106,maxm=4000;

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

struct edge
{
	int v,w,next;
}e[maxm];

int head[maxn],tot,kase,n,m;
int d[maxn],cnt[maxn];
bool inq[maxn];

void add(int u,int v,int w)
{
	e[++tot].v=v;
	e[tot].w=w;
	e[tot].next=head[u];
	head[u]=tot;
}

bool spfa()
{
	std::queue<int> q;
	memset(inq,0,sizeof inq);
	memset(d,0x3f,sizeof d);
	memset(cnt,0,sizeof cnt);
	d[n+1]=0,inq[n+1]=1,cnt[n+1]=1;
	q.push(n+1);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=head[u];i;i=e[i].next)
		{
			int &v=e[i].v,&w=e[i].w;
			if(d[u]+w<d[v])
			{
				d[v]=d[u]+w;
				if(!inq[v])
				{
					if(++cnt[v]>n)
						return false;
					inq[v]=1;
					q.push(v);
				}
			}
		}
	}
	return true;
}

int main()
{
	kase=read();
	while(kase--)
	{
		n=read(),m=read();
		tot=0;
		memset(head,0,sizeof head);
		for(int i=0;i<=n;i++)
			add(n+1,i,0);
		while(m--)
		{
			int s=read()-1,t=read(),v=read();
			add(s,t,v);
			add(t,s,-v);
		}
		if(spfa())
			printf("true\n");
		else
			printf("false\n");
	}
	return 0;
}
