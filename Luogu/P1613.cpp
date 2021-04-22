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

inline ll min(ll a,ll b)
{
	return a<b?a:b;
}

const int maxn=53;
ll dis[maxn][maxn],n,m;
bool G[maxn][maxn][64];

int main()
{
	memset(dis,0x3f,sizeof dis);
	n=read(),m=read();
	while(m--)
	{
		int x=read(),y=read();
		G[x][y][0]=true;
		dis[x][y]=1;
	}
	for(int k=1;k<=64;k++)
		for(int x=1;x<=n;x++)
			for(int y=1;y<=n;y++)
				for(int z=1;z<=n;z++)
					if(G[x][z][k-1] && G[z][y][k-1])
						G[x][y][k]=true,dis[x][y]=1;
	for(int x=1;x<=n;x++)
		for(int y=1;y<=n;y++)
			for(int z=1;z<=n;z++)
				dis[x][y]=min(dis[x][y],dis[x][z]+dis[z][y]);
	printf("%lld\n",dis[1][n]);
	return 0;
}
