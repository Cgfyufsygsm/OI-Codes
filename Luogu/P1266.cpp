#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>

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

struct edge
{
	int from,to,v,l;
	double t;
	edge(){}
	edge(int a,int b,int c,int d)
	{
		from=a;
		to=b;
		v=c;
		l=d;
		t=(v==0?-1e8:(double)l/(double)v);
	}
};

struct node
{
	double d;
	int now;
	int v;
	node(){}
	node(double dd,int nnow,int vv)
	{
		d=dd;
		now=nnow;
		v=vv;
	}
};

bool operator<(const node &a,const node &b)
{
	return a.d>b.d;
}

//城市编号从0开始 
const int maxn=150+5;
std::vector<edge> G[maxn];
int n,m,t,from[maxn][505],fromv[maxn][505];
double d[maxn][505];
bool vis[maxn][505];

void add(int from,int to,int v,int l)
{
	G[from].push_back(edge(from,to,v,l));
	return;
}

void dijkstra()
{
	std::priority_queue<node> q;
    memset(d,127,sizeof(d));
    d[0][70]=0;
    q.push(node(0,0,70));
    while (!q.empty())
    {
        int now=q.top().now,v=q.top().v;
        q.pop();
        if(!vis[now][v])
        {
            vis[now][v]=1;
            for(auto &e:G[now])
            {
                if(e.v)
                {
                	if(d[e.to][e.v]>d[now][v]+e.t)
                	{
                		d[e.to][e.v]=d[now][v]+e.t;
                		q.push(node(d[e.to][e.v],e.to,e.v));
                		from[e.to][e.v]=now;
                		fromv[e.to][e.v]=v;
					}
				}
				else
				{
					if(d[e.to][v]>d[now][v]+(double)e.l/(double)v)
					{
						d[e.to][v]=d[now][v]+(double)e.l/(double)v;
						q.push(node(d[e.to][v],e.to,v));
						from[e.to][v]=now;
						fromv[e.to][v]=v;
					}
				}
            }
        }
    }
    return;
}

void Find_way(int now,int v)
{
	if(now!=0)
		Find_way(from[now][v],fromv[now][v]);
	printf("%d ",now);
}

int main()
{
	n=read(),m=read(),t=read();
	for(int i=1;i<=m;i++)
	{
		int a=read(),b=read(),c=read(),d=read();
		add(a,b,c,d);
	}
	dijkstra();
	int ansv;
	double mint=1e9;
	for(int i=1;i<=500;i++)
		if(mint>d[t][i])
			ansv=i,mint=d[t][i];
	Find_way(t,ansv);
	return 0;
}
