#include <cstdio>
#include <cstring>

const int maxn=1e3+5,maxm=205,mod=1e9+7;
int n,m,k;

char a[maxn],b[maxm];

int f[2][maxn][maxm][2];

inline int max(int a,int b)
{
	return a>b?a:b;
}

int main()
{
	scanf("%d %d %d",&n,&m,&k);
	scanf("%s%s",a+1,b+1);
	f[0][0][0][0]=f[1][0][0][0]=1;
	for(int i=1,val=1;i<=n;i++,val^=1)
		for(int j=1;j<=m;j++)
			for(int p=1;p<=k;p++)
				if(a[i]==b[j])
				{
					f[val][j][p][0]=(f[val^1][j][p][0]+f[val^1][j][p][1])%mod;
					f[val][j][p][1]=(f[val^1][j-1][p][1]+(f[val^1][j-1][p-1][1]+f[val^1][j-1][p-1][0])%mod)%mod;
				}
				else
				{
					f[val][j][p][0]=(f[val^1][j][p][0]+f[val^1][j][p][1])%mod;
					f[val][j][p][1]=0;
				}
	printf("%d\n",(f[n&1][m][k][0]+f[n&1][m][k][1])%mod);
	return 0;
}
