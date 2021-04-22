#include <cstdio>
#include <stack>
using namespace std;

stack<int> a;
char s[1200];

int main()
{
	scanf("%s",s);
	int p=0;
	int x,y;
	for(int i=0;s[i]!='@';i++)
	{
		switch(s[i])
		{
			case '.':
				a.push(p);
				p=0;
				break;
			case '*':
				x=a.top();
				a.pop();
				y=a.top();
				a.pop();
				a.push(x*y);
				break;
			case '+':
				x=a.top();
				a.pop();
				y=a.top();
				a.pop();
				a.push(x+y);
				break;
			case '-':
				x=a.top();
				a.pop();
				y=a.top();
				a.pop();
				a.push(y-x);
				break;
			case '/':
				x=a.top();
				a.pop();
				y=a.top();
				a.pop();
				a.push(y/x);
				break;
			default:
				p*=10;
				p+=(s[i]-'0');
				break;
		}
	}
	printf("%d",a.top());
	return 0;
}
