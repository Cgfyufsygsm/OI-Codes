#include <cstdio>
#include <cctype>
#include <cstring> 

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

const int maxn=55;
int x[maxn],p[maxn];
int n,c;
int f[maxn][maxn][2];

inline int dis(int i,int j)
{
	return x[j]-x[i];
}

inline int sum(int i,int j)
{
	return p[j]-p[i-1];
}

inline int min(int a,int b)
{
	return a<b?a:b;
}

int main()
{
	n=read(),c=read();
	for(int i=1;i<=n;i++)
		x[i]=read(),p[i]=read()+p[i-1];
	memset(f,0x3f,sizeof f);
	f[c][c][0]=f[c][c][1]=0;
	for(int i=c;i;i--)
		for(int j=i+1;j<=n;j++)
		{
			f[i][j][0]=min(f[i+1][j][0]+dis(i,i+1)*(sum(j+1,n)+sum(1,i)),f[i+1][j][1]+dis(i,j)*(sum(j+1,n)+sum(1,i)));
			f[i][j][1]=min(f[i][j-1][0]+dis(i,j)*(sum(1,i-1)+sum(j,n)),f[i][j-1][1]+dis(j-1,j)*(sum(1,i-1)+sum(j,n)));
		}
	printf("%d\n",min(f[1][n][0],f[1][n][1]));
	return 0;
}
