#include <cstdio>
#include <cstring>
#include <cmath>

int n,m;//m is the range
bool prime[1000005];
int qzh[1000005];

void make_prime()
{
    memset(prime,1,sizeof(prime));
    prime[0]=prime[1]=0;
    for(int i=2;i<=sqrt(m)+1;i++)
    {
        if(prime[i])
            for(int j=2*i;j<=m;j+=i)
                prime[j]=0;
    }
    return;
}

int main()
{
    scanf("%d %d", &n, &m);
    make_prime();
    for(int i=0;i<=m;i++)
    {
        qzh[i]=qzh[i-1];
        if(prime[i])
            qzh[i]++;
    }
    for(int i=1;i<=n;i++)
    {
        int l,r;
        scanf("%d %d", &l, &r);
        if(l<1||r>m)
            printf("Crossing the line\n");
        else
            printf("%d\n",qzh[r]-qzh[l-1]);
    }
    return 0;
}