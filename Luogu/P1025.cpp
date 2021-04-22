#include <iostream>
using namespace std;
typedef long long ll;
ll f[300][50];
int n,k;
int main()
{
	cin>>n>>k;
	for (int i=1;i<=n;i++) 
	{
		f[i][1]=1;
		f[i][0]=1;
	}
	for (int x=2;x<=k;x++)
	{
		f[1][x]=0;
		f[0][x]=0;
	}
	for (int i=2;i<=n;i++)
        for (int x=2;x<=k;x++)
            if (i>x)
				f[i][x]=f[i-1][x-1]+f[i-x][x];
            else
				f[i][x]=f[i-1][x-1];
    cout<<f[n][k];
    return 0;
}
