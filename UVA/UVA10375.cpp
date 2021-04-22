#include <cstdio>
#include <cctype>
#include <cstring>
#include <vector>
#include <cmath>

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

bool is_prime[10005];
int e[10005];
int p,q,r,s;
std::vector<int> prime;

void make_prime()
{
    is_prime[0]=is_prime[1]=0;
    for(int i=2;i<=10000;++i)
        is_prime[i]=1;
    for(int i=2;i<=10000;++i)
    {
        if(is_prime[i])
            prime.push_back(i);
        else continue;
        for(int j=2;i*j<=10000;++j)
            is_prime[i*j]=false;
    }
    return;
}

void add_int(int n,int d)
{
    for(int i=0;i<prime.size();++i)
    {
        while(n%prime[i]==0)
        {
            n/=prime[i];
            e[i]+=d;
        }
        if(n==1)return;
    }
}

void add_fact(int n,int d)
{
    for(int i=1;i<=n;++i)
        add_int(i,d);
    return;
}

int main()
{
    make_prime();
    while(scanf("%d %d %d %d",&p,&q,&r,&s)!=EOF)
    {
        memset(e,0,sizeof e);
        add_fact(p,1);
        add_fact(q,-1);
        add_fact(p-q,-1);
        add_fact(r,-1);
        add_fact(s,1);
        add_fact(r-s,1);
        double ans=1;
        for(int i=0;i<prime.size();++i)
            ans*=pow(prime[i],e[i]);
        printf("%.5lf\n",ans);
    }
    return 0;
}