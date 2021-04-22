#include <cstdio>
#include <cstring>
typedef long long ll;

const int maxn=1100;
ll n,f[maxn];
bool isprime[maxn];
int tot,prime[maxn];

void make_prime()
{
    memset(isprime,1,sizeof(isprime));
    isprime[1]=isprime[0]=0;
    for(int i=2;i<=n;i++)
    {
        if(!isprime[i]) continue;
        for(int j=2;i*j<=n;j++) isprime[i*j]=0;
    }
    for(int i=2;i<=n;i++)
        if(isprime[i])
            prime[++tot]=i;
    return;
}

int main()
{
    scanf("%lld",&n);
    make_prime();
    f[0]=1;
    for(int i=1;i<=tot;i++)
        for(int j=prime[i];j<=n;j++)
            f[j]+=f[j-prime[i]];
    printf("%lld\n",f[n]);
    return 0;
}