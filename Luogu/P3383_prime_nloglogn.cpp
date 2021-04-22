#include <cstdio>
#include <cstring>

bool prime[(int)1e7+5];
int n;

void make_prime()
{
    memset(prime,1,sizeof(prime));
    prime[1]=prime[0]=0;
    for(int i=2;i<=n;i++)
    {
        if(!prime[i]) continue;
        for(int j=2;i*j<=n;j++) prime[i*j]=0;
    }
    return;
}

int main()
{
    scanf("%d",&n);
    int m;
    scanf("%d",&m);
    make_prime();
    for(int i=1;i<=m;i++)
    {
        int tmp;
        scanf("%d",&tmp);
        printf("%s",prime[tmp]?"Yes\n":"No\n");
    }
    return 0;
}