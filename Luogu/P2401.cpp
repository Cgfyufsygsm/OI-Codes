#include <cstdio>

int f[1005][1005];
const int mod=2015;
//f[i][j]

int main()
{
	int n,k;
	scanf("%d %d",&n,&k);
	f[1][1]=0;
	for(int i=1;i<=n;i++)
		f[i][0]=1;
	for(int i=2;i<=n;i++)
		for(int k=1;k<i;k++)
			f[i][k]=(k+1)*f[i-1][k]+(i-k)*f[i-1][k-1],
			f[i][k]%=mod;
	printf("%d\n",f[n][k]);
	return 0;
}
