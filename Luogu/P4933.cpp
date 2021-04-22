#include <cstdio>
#include <cctype>
using namespace std;

const int maxn=1005,mod=998244353;
int n,h[maxn];
int ans,f[maxn][20005<<1];

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        h[i]=read();
    for(int i=1;i<=n;i++)
    {
        ans++;
        for(int j=1;j<i;j++)
        {
            int cur=h[i]-h[j]+20000;
            f[i][cur]+=f[j][cur]+1;
            f[i][cur]%=mod;
            ans+=f[j][cur]+1;
            ans%=mod;
        }
    }
    printf("%d\n",ans%mod);
    return 0;
}