#include <cstdio>
#include <cctype>

const int mod=10001;
int n,a,b;
long long x[mod];

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
    n=read()<<1;
    for(int i=1;i<=n;++i)
        if(i&1)
            x[i]=read();
    for(a=1;a<=10000;a++)
    {
        for(b=1;b<=10000;b++)
        {
            bool flag=true;
            for(int i=2;i<=n;++i)
            {
                if(!(i&1))
                    x[i]=(a*x[i-1]+b)%mod;
                else
                {
                    int tmp=(a*x[i-1]+b)%mod;
                    if(tmp!=x[i])
                    {
                        flag=false;
                        break;
                    }
                }
            }
            if(flag)
            {
                for(int i=1;i<=n;++i)
                    if(!(i&1))
                        printf("%d\n",x[i]);
                return 0;
            }
        }
    }
    return 0;
}