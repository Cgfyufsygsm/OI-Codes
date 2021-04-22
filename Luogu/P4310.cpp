#include <cstdio>
#include <cctype>

inline int read()
{
    char c = getchar();
    int s = 0, x = 1;
    while (!isdigit(c))
    {
    	if(c=='-')
    		x = -x;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s*x;
}

inline int max(int a,int b)
{
	return a>b?a:b;
}

int f[33];

int main()
{
	int n,a,ans=0;
	n=read();
	while(n--)
	{
		a=read();
		int maxx=1;
		for(int i=0;i<=30;i++)
			if(a&(1<<i))
				maxx=max(maxx,f[i]+1);
		for(int i=0;i<=30;i++)
			if(a&(1<<i))
				f[i]=max(f[i],maxx);
		ans=max(ans,maxx);
	}
	printf("%d\n",ans);
	return 0;
}
