#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
    {
        if(c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn=505;

int n,m;
int h[maxn][maxn],l[maxn][maxn],r[maxn][maxn];

bool vis[maxn][maxn],used[maxn];

const int fx[]={1,-1,0,0};
const int fy[]={0,0,1,-1};

inline bool chk(int i,int j)
{
	return i>=1 && i<=n && j>=1 && j<=m;
}

void dfs(int i,int j)
{
	vis[i][j]=1;
	for(int k=0;k<4;k++)
	{
		int ii=i+fx[k],jj=j+fy[k];
		if(ii<1 || ii>n || jj<1 || jj>m)continue;
		if(h[ii][jj]>=h[i][j])continue;
		if(!vis[ii][jj])dfs(ii,jj);
		l[i][j]=min(l[i][j],l[ii][jj]);
		r[i][j]=max(r[i][j],r[ii][jj]);
	}
	return;
}

int main()
{
	n=read(),m=read();
	memset(l,0x3f,sizeof l);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			h[i][j]=read();
	for(int i=1;i<=m;i++)
		l[n][i]=r[n][i]=i;
	for(int i=1;i<=m;i++)
		if(!vis[1][i])
			dfs(1,i);
	int vised=0;
	for(int j=1;j<=m;j++)
		vised+=(!vis[n][j]);
	if(vised)
	{
		printf("0\n");
		printf("%d\n",vised);
		return 0;
	}
	int left=1;
	int ans=0;
	while(left<=m)
	{
		int maxr=0;
		for(int i=1;i<=m;i++)
			if(l[1][i]<=left)
				maxr=max(maxr,r[1][i]);
		ans++;
		left=maxr+1;
	}
	printf("1\n%d\n",ans);
	return 0;
}
