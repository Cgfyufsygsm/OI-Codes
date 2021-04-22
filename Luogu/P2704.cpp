#include <cstdio>

const int N=105,M=12;
char a[N][M];
int F[N];
int f[2][80][80];//f[i][j][k]第i行状态为j,i-1行为k的最多炮兵个数
int n,m;

int st[80],tot;
int cnt[80];

void dfs(int state,int sum,int i)
{
	if(i>=m)
	{
		st[++tot]=state;
		cnt[tot]=sum;
		return;
	}
	dfs(state,sum,i+1);
	dfs(state+(1<<i),sum+1,i+3);
	return;
}

inline int max(int a,int b)
{
	return a>b?a:b;
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			F[i]<<=1;
			if(a[i][j]=='P')
				F[i]+=1;
		}
	dfs(0,0,0);
	for(int i=1;i<=tot;i++)
		if((st[i]&F[2])==st[i])
			for(int j=1;j<=tot;j++)
				if(((st[j]&F[1])==st[j]) && ((st[i]&st[j])==0))
					f[0][i][j]=cnt[i]+cnt[j];
	for(int l=3;l<=n;l++)
		for(int i=1;i<=tot;i++)
		{
			if((st[i]&F[l])!=st[i])
				continue;
			for(int j=1;j<=tot;j++)
			{
				if(((st[j]&F[l-1])!=st[j]) || (st[j]&st[i]))
					continue;
				for(int k=1;k<=tot;k++)
				{
					if(((st[k]&F[l-2])!=st[k]) || (st[j]&st[k]) || (st[i]&st[k]))
						continue;
					f[l&1][i][j]=max(f[l&1][i][j],f[(l-1)&1][j][k]+cnt[i]);
				}
			}
		}
	int ans=0;
	for(int i=1;i<=tot;i++)
		for(int j=1;j<=tot;j++)
			if(((st[i]&st[j])==0) && ((st[i]&F[n])==st[i]) && ((st[j]&F[n-1])==st[j]))
				ans=max(ans,f[n&1][i][j]);
	printf("%d\n",ans);
	return 0;
}
