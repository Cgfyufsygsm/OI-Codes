#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn=1e6+5;
int f[maxn][21],n,m,lg[maxn];

int main()
{
    scanf("%d %d",&n,&m);
    lg[0]=-1,lg[1]=0;
    for(int i=2;i<=n;i++)
        lg[i]=lg[i/2]+1;
    for(int i=1;i<=n;i++)
        scanf("%d",&f[i][0]);
    for(int j=1;j<=20;j++)
        for(int i=1;i<=n;i++)
            f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    for(int i=1,j=m;j<=n;i++,j++)
    {
        int s=lg[j-i+1];
        printf("%d\n",min(f[i][s],f[j-(1<<s)+1][s]));
    }
    return 0;
}