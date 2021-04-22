#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn=1e5+10;

int f[17][maxn],lg[maxn];

inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
#endif
    int n=read(),m=read(),l,r;
    lg[1]=0;lg[0]=-1;
    for (int i=2; i<=n; i++)
		lg[i]=lg[i/2]+1;
    for(int i=1;i<=n;i++) f[0][i]=read();
    for(int j=1;j<17;j++)
        for(int i=1;i<=n;i++)
            f[j][i]=max(f[j-1][i],f[j-1][i+(1<<(j-1))]);
    while(m--)
    {
        l=read(),r=read();
        int s=lg[r-l+1];
        printf("%d\n",max(f[s][l],f[s][r-(1<<s)+1]));
    }
    return 0;
}
