#include <cstdio>
#include <cstring>

typedef long long ll;

const int maxn=100;
int T;
int n;
ll f[maxn][maxn];
char s[maxn];

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s+1);
        n=strlen(s+1);
        memset(f,0,sizeof f);
        for(int i=1;i<=n;i++)
            f[i][i]=1ll;
        for(int len=2;len<=n;len++)
            for(int i=1,j=i+len-1;j<=n;i++,j++)
                if(s[i]==s[j])
                    f[i][j]=f[i+1][j]+f[i][j-1]+1ll;
                else
                    f[i][j]=f[i+1][j]+f[i][j-1]-f[i+1][j-1];
        printf("%lld\n",f[1][n]);
    }
    return 0;
}