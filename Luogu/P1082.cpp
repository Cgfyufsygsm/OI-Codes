#include <cstdio>

int a,b,gcd;

void exgcd(int &x,int &y,int a,int b)
{
	if(b==0)
	{
		gcd=a;
		x=1;y=0;
		return;
	}
	exgcd(y,x,b,a%b);
	y-=a/b*x;
}

int main()
{
	scanf("%d %d",&a,&b);
	int x,y;
	exgcd(x,y,a,b);
	printf("%d\n",(x+b)%b);
	return 0;
}
