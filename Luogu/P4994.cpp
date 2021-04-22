#include <cstdio>

int f[3];

int main()
{
    int m;
    scanf("%d",&m);
    f[1]=1;
    for(int n=2;;++n)
    {
        f[n%3]=(f[(n-1)%3]+f[(n-2)%3])%m;
        if(f[n%3]%m==1 && f[(n-1)%3]%m==0)
        {
            printf("%d\n",n-1);
            return 0;
        }
    }
}