#include<iostream>
using namespace std;
typedef long long ll;
ll f[31][31];//f[i][j]为经过j次传球到达i的可能性
//dp:f[i][j]=f[i+1][j-1]+f[i-1][j-1]
int n,m;
int main()
{
	cin>>n>>m;
	f[1][0]=1;
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<=n;i++)
		{
			f[i][j]=f[i+1>n?1:i+1][j-1]+f[i-1<1?n:i-1][j-1];
		}
	}
	cout<<f[1][m]<<endl;
	return 0;
} 
