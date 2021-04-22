#include <cstdio>

const int N=10,M=1<<N;

long long f[N][M][N*N];
int st[M],king[M];
int n,K,cnt;

void dfs(int state,int sum,int i)
{
	if(i>=n)
	{
		st[++cnt]=state;
		king[cnt]=sum;
		return;
	}
	dfs(state,sum,i+1);
	dfs(state+(1<<i),sum+1,i+2);
	return;
}

int main()
{
	scanf("%d %d",&n,&K);
	dfs(0,0,0);
	for(int i=1;i<=cnt;i++)
		f[1][i][king[i]]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=cnt;j++)
			for(int k=1;k<=cnt;k++)
			{
				if((st[j]&st[k]) || ((st[j]<<1)&st[k]) || ((st[j])>>1&st[k]))
					continue;
				for(int s=K;s>=king[j];s--)
					f[i][j][s]+=f[i-1][k][s-king[j]];
			}
	long long ans=0;
	for(int i=1;i<=cnt;i++)
		ans+=f[n][i][K];
	printf("%lld\n",ans);
	return 0;
}
