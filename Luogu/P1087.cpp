#include <iostream>
#include <string>
#define DAD(x) (x>>1)
#define LF(x) ((x)<<1)
#define RT(x) (((x)<<1)+1)
using namespace std;
string s;
int n,maxn;

struct node{
	string s;
	char type;
}t[3000];

void make_tree(string s,int cur)
{
	t[cur].s=s;
	int len=s.length();
	if(len!=1)
	{
		string left(s,0,len/2);
		string right(s,len/2,len/2);
		make_tree(left,LF(cur));
		make_tree(right,RT(cur));
	}
	return;
}

char dfs(int cur)
{
	char a,b;
	if(t[cur].s.length()>1)
	{
		//cout<<cur<<endl;
		a=dfs(LF(cur));
		b=dfs(RT(cur));
		if(a!=b||a=='F'||b=='F') t[cur].type='F';
		if(a=='I'&&b=='I') t[cur].type='I';
		if(a=='B'&&b=='B') t[cur].type='B';
	}
	else
	{
		t[cur].type=t[cur].s=="0"?'B':'I';
	}
	printf("%c",t[cur].type);
	return t[cur].type;
}

int main()
{
	cin>>n>>s;
	maxn=1<<n;
	make_tree(s,1);
	dfs(1);
	return 0;
}

