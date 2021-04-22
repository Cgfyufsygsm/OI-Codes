#include <iostream>
using namespace std;

const int biao[10][10]=
{{0,0,0,0,0,0,0,0,0,0},
{0,6,6,6,6,6,6,6,6,6},
{0,6,7,7,7,7,7,7,7,6},
{0,6,7,8,8,8,8,8,7,6},
{0,6,7,8,9,9,9,8,7,6},
{0,6,7,8,9,10,9,8,7,6},
{0,6,7,8,9,9,9,8,7,6},
{0,6,7,8,8,8,8,8,7,6},
{0,6,7,7,7,7,7,7,7,6},
{0,6,6,6,6,6,6,6,6,6}};
bool line[11][11],col[11][11],area[11][11];
int cnt=0,cntline[11]={0},cntcol[11]={0};
int maze[11][11]={0};
int ans=-1;

int id(int l,int c)
{
	if(l>=1&&l<=3)
	{
		if(c>=1&&c<=3)
			return 1;
		if(c>=4&&c<=6)
			return 2;
		else
			return 3;
	}
	else if(l>=4&&l<=6)
	{
		if(c>=1&&c<=3)
			return 4;
		if(c>=4&&c<=6)
			return 5;
		else
			return 6;
	}
	else
	{
		if(c>=1&&c<=3)
			return 7;
		if(c>=4&&c<=6)
			return 8;
		else
			return 9;
	}
}
int calc()
{
	int sum=0;
	for(int l=1;l<=9;l++)
	{
		for(int c=1;c<=9;c++)
		{
			sum+=(maze[l][c]*biao[l][c]);
		}
	}
	return sum;
}
void dfs(int l,int c,int already)
{
	if(already==81)
	{
		int a=calc();
		//cout<<a<<endl;
		ans=a>ans?a:ans;
		return;
	}
	for(int k=1;k<=9;k++)
	{
		if(line[l][k]||col[c][k]||area[id(l,c)][k])
			continue;
		maze[l][c]=k;
		line[l][k]=1;
		col[c][k]=1;
		area[id(l,c)][k]=1;
		cntline[l]++;
		cntcol[c]++;
		int nxtl=0,nxtc=0,ll=-1,cc=-1;
		for(int i=1;i<=9;i++)
		{
			if(cntline[i]>ll&&cntline[i]<9)
			{
				ll=cntline[i];
				nxtl=i;
			}
		}
		for(int j=1;j<=9;j++)
		{
			if(cntcol[j]>cc&&(!maze[nxtl][j]))
			{
				cc=cntcol[j];
				nxtc=j;
			}
		}
		dfs(nxtl,nxtc,already+1);
		maze[l][c]=0;
		line[l][k]=0;
		col[c][k]=0;
		area[id(l,c)][k]=0;
		cntline[l]--;
		cntcol[c]--;
	}
}

int main()
{
	for(int l=1;l<=9;l++)
	{
		for(int c=1;c<=9;c++)
		{
			cin>>maze[l][c];
			if(maze[l][c])
			{
				cnt++;
				cntline[l]++;
				cntcol[c]++;
				line[l][maze[l][c]]=1;
				col[c][maze[l][c]]=1;
				area[id(l,c)][maze[l][c]]=1;
			}
		}
	}
	int fstl=0,fstc=0,ll=-1,cc=-1;
	for(int l=1;l<=9;l++)
	{
		if(cntline[l]>ll&&cntline[l]<9)
		{
			ll=cntline[l];
			fstl=l;
		}
	}
	for(int c=1;c<=9;c++)
	{
		if(cntcol[c]>cc&&(!maze[fstl][c]))
		{
			cc=cntcol[c];
			fstc=c;
		}
	}
	dfs(fstl,fstc,cnt);
	cout<<ans<<endl;
	return 0;
}
