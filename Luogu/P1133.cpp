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

const int maxn=100000+5,INF=0x3f3f3f3f;
int n,val[maxn][4];
int f[maxn][4][4];

//f[i][j][k]: 1为k，当前为j  j,k定义：0为高度最矮，1为中间充当矮的那个，2为中间高的，3为最高 

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		val[i][0]=read(),val[i][1]=val[i][2]=read(),val[i][3]=read();
	memset(f,-INF,sizeof f);
	f[1][0][0]=val[1][0],f[1][1][1]=f[1][2][2]=val[1][1],f[1][3][3]=val[1][3];
	for(int i=2;i<=n;i++)
	{
		for(int k=0;k<4;k++)
		{
			f[i][0][k]=max(f[i-1][2][k],f[i-1][3][k])+val[i][0];
			f[i][1][k]=f[i-1][3][k]+val[i][1];
			f[i][2][k]=f[i-1][0][k]+val[i][2];
			f[i][3][k]=max(f[i-1][1][k],f[i-1][0][k])+val[i][3];
			for(int j=0;j<4;j++)
				if(f[i][j][k]<0)
					f[i][j][k]=-INF;
		}
	}
	printf("%d\n",max(max(f[n][0][3],f[n][0][2]),max(max(f[n][1][3],f[n][2][0]),max(f[n][3][0],f[n][3][1]))));
}
