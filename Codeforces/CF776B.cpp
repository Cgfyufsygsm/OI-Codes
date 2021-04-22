#include <cstdio>
#include <cstring>

bool prime[(int)1e5+10];
int n;

void make_prime()
{
    memset(prime,1,sizeof(prime));
    prime[1]=prime[0]=0;
    for(int i=2;i*i<=n+1;i++)
    {
        if(!prime[i]) continue;
        for(int j=2;i*j<=n+5;j++) prime[i*j]=0;
    }
    return;
}

int main()
{
    scanf("%d",&n);
    if(n<3)
    {
        printf("1\n1 ");
        if(n==2) printf("1\n");
        return 0;
    }
    make_prime();
    printf("2\n");
    for(int i=1;i<=n;i++)
        printf("%d ",prime[i+1]?1:2);
    return 0;
}