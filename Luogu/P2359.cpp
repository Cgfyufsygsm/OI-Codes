#include <cstdio>
#include <cstring>

int n;
int f[100050][10][10];

bool is_prime[1005];

const int mod=1e9+9;

int main()
{
    memset(is_prime,1,sizeof is_prime);
    is_prime[1]=is_prime[0]=0;
    for(int i=2;i<=1000;i++)
    {
        if(!is_prime[i])
            continue;
        for(int j=2;i*j<=1000;j++)
            is_prime[i*j]=0;
    }
    for(int i=100;i<=999;i++)
    {
        if(!is_prime[i])
            continue;
        ++f[3][(i%100)/10][i%10];
    }
    scanf("%d",&n);
    for(int i=4;i<=n;i++)
        for(int a=1;a<=9;a++)
            for(int b=0;b<=9;b++)
                for(int c=0;c<=9;c++)
                    if(is_prime[a*100+b*10+c])
                        f[i][b][c]+=f[i-1][a][b],
                        f[i][b][c]%=mod;
    int ans=0;
    for(int i=0;i<=9;i++)
        for(int j=0;j<=9;j++)
            ans+=f[n][i][j],
            ans%=mod;
    printf("%d\n",ans);
    return 0;
}