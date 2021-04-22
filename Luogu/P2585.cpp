#include <cstdio>
#include <algorithm>

using std::max;
using std::min;

const int maxn=5e5+5;
int dfn;
int f[maxn][3][2];//f[k][i][0/1]表示k号节点刷了i号色后最多/少有多少个绿色节点 

//1是最多，0是最少
//0 1 2: RGB 

#define R 0
#define G 1
#define B 2

int dfs()
{
	int now=++dfn;
	int x=getchar()-'0';
	f[now][G][1]=f[now][G][0]=1;
	if(x==1)
	{
		int son=dfs();
		f[now][R][1]=max(f[son][B][1],f[son][G][1]);
		f[now][R][0]=min(f[son][B][0],f[son][G][0]);
		f[now][B][1]=max(f[son][R][1],f[son][G][1]);
		f[now][B][0]=min(f[son][R][0],f[son][G][0]);
		f[now][G][1]+=max(f[son][R][1],f[son][B][1]);
		f[now][G][0]+=min(f[son][R][0],f[son][B][0]);
	}
	else if(x==2)
	{
		int s1=dfs(),s2=dfs();
		f[now][R][1]=max(f[s1][B][1]+f[s2][G][1],f[s2][B][1]+f[s1][G][1]);
		f[now][R][0]=min(f[s1][B][0]+f[s2][G][0],f[s2][B][0]+f[s1][G][0]);
		f[now][B][1]=max(f[s1][R][1]+f[s2][G][1],f[s2][R][1]+f[s1][G][1]);
		f[now][B][0]=min(f[s1][R][0]+f[s2][G][0],f[s2][R][0]+f[s1][G][0]);
		f[now][G][1]+=max(f[s1][R][1]+f[s2][B][1],f[s2][R][1]+f[s1][B][1]);
		f[now][G][0]+=min(f[s1][R][0]+f[s2][B][0],f[s2][R][0]+f[s1][B][0]);
	}
	return now;
}

int main()
{
	dfs();
	printf("%d %d",max(f[1][G][1],max(f[1][R][1],f[1][B][1])),min(f[1][G][0],min(f[1][B][0],f[1][R][0])));
	return 0; 
}
