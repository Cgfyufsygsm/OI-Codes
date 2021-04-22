#include<stdio.h>
int main()
{
    long n,x,count,i,c,b;
    scanf("%ld%ld",&n,&x);
    for ( i = 1; i <= n; i++)
    {
        b=i;
        while(b!=0)
        {
            c=b%10;
            b/=10;
            if(c==x)
            {
                count++;
            }
        }
    }
    printf("%ld",count);
    return 0;
}
