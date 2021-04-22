#include <cstdio>
#include <cctype>

const int N=13,mod=100000000,M=1<<N;
int n,m,a[N][N];
int f[N][M],F[N];
bool st[M];

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			F[i]=(F[i]<<1)+a[i][j]; 
		}
	for(int i=0;i<(1<<m);i++)
		st[i]=((i&(i<<1))==0) && ((i&(i>>1))==0);
	f[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<(1<<m);j++)
			if(st[j] && ((j & F[i])==j))
				for(int k=0;k<(1<<m);k++)
					if((k&j)==0)
						f[i][j]=(f[i][j]+f[i-1][k])%mod;
	int ans=0;
	for(int i=0;i<(1<<m);i++)
		ans=(ans+f[n][i])%mod;
	printf("%d\n",ans);
	return 0;
}
