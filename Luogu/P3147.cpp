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

const int maxn=(1<<18)+5;
int n,f[60][maxn];

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		f[read()][i]=i;
	int ans=0;
	for(int i=1;i<=58;i++)
		for(int j=1;j<=n;j++)
			if(!f[i][j] && f[i-1][j] && f[i-1][f[i-1][j]+1])
				f[i][j]=f[i-1][f[i-1][j]+1],
				ans=i;
	printf("%d\n",ans);
	return 0;
}
