#include <cstdio>
#include <cctype>
#define L (k<<1)
#define R (L|1)
#define M (i+j>>1)

inline int max(int a,int b)
{
	return a>b?a:b;
}

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

const int maxn=500000+5;
int n,m;

struct tree
{
	int pre,suf,sum,ans;
	tree operator+(const tree &b)const
	{
		tree ret;
		ret.pre=max(pre,sum+b.pre);
		ret.suf=max(b.suf,suf+b.sum);
		ret.ans=max(max(ans,b.ans),suf+b.pre);
		ret.sum=sum+b.sum;
		return ret;
	}
	tree operator=(const int &x)
    {
        pre=suf=ans=sum=x;
        return *this;
    }
}f[maxn<<2];

void build(int i,int j,int k)
{
	if(i==j)
	{
		f[k]=read();
		return;
	}
	build(i,M,L);
	build(M+1,j,R);
	f[k]=f[L]+f[R];
	return;
}

void modify(int i,int j,int k,int x,int d)
{
	if(i==j)
	{
		f[k]=d;
		return;
	}
	if(x<=M)
		modify(i,M,L,x,d);
	else
		modify(M+1,j,R,x,d);
	f[k]=f[L]+f[R];
	return;
}

tree query(int i,int j,int k,int x,int y)
{
	if(x<=i && y>=j)
		return f[k];
	if(y<=M)
		return query(i,M,L,x,y);
	if(x>M)
		return query(M+1,j,R,x,y);
	return query(i,M,L,x,M)+query(M+1,j,R,M+1,y); 
}

int main()
{
	n=read(),m=read();
	build(1,n,1);
	while(m--)
	{
		int k=read(),x=read(),y=read();
		if(k==1)
			printf("%d\n",query(1,n,1,x+y-max(x,y),max(x,y)).ans);
		else
			modify(1,n,1,x,y);
	}
	return 0;
}
