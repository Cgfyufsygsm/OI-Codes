#include <cstdio>
#include <iostream>
using namespace std;
void dfs(int cur);
struct node{
	int left,right;
	node(){
		left=right=-1;
	}
}tree[28];

int main()
{
	int n;
	scanf("%d",&n);
	char a,b,c;
	cin>>a>>b>>c;
	if(b!='*')tree[a-'a'+1].left=b-'a'+1;
	if(c!='*')tree[a-'a'+1].right=c-'a'+1;
	for(register int i=2;i<=n;i++)
	{
		char a,b,c;
		cin>>a>>b>>c;
		if(b!='*')tree[a-'a'+1].left=b-'a'+1;
		if(c!='*')tree[a-'a'+1].right=c-'a'+1;
	}
	dfs(a-'a'+1);
	return 0;
}

void dfs(int cur)
{
	printf("%c",cur-1+'a');
	if(tree[cur].left!=-1) dfs(tree[cur].left);
	if(tree[cur].right!=-1) dfs(tree[cur].right);
	return;
}
