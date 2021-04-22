#include <cstdio>
#include <cctype>

inline int read()
{
    int s=0;
    char c=getchar();
    while(!isdigit(c))
        c=getchar();
    while(isdigit(c))
        s=s*10+c-'0',c=getchar();
    return s;
}

const int mod=19650827,maxn=1005;
int n,a[maxn];
int f[maxn][maxn][2];
//f[i][j][0/1] 0：初始队形以a[i]结尾，1：以a[j]结尾，表示 (j-i+1) 个人排出理想队形中 [i,j] 的方案数

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),f[i][i][0]=1;
	for(int len=2;len<=n;len++)
		for(int i=1,j=i+len-1;j<=n;i++,j++)
		{
			if(a[i]<a[i+1])
				f[i][j][0]=(f[i][j][0]+f[i+1][j][0])%mod;
			if(a[i]<a[j])
				f[i][j][0]=(f[i][j][0]+f[i+1][j][1])%mod;
			if(a[j]>a[i])
				f[i][j][1]=(f[i][j][1]+f[i][j-1][0])%mod;
			if(a[j]>a[j-1])
				f[i][j][1]=(f[i][j][1]+f[i][j-1][1])%mod;
		}
	printf("%d\n",(f[1][n][0]+f[1][n][1])%mod);
	return 0;
}
