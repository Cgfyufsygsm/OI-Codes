#include <cstdio>


inline bool chk(int a,int b)
{
    if(a>98765 || b>98765 || a<1234 || b<1234)
        return false;
    int x[11];
    for(int i=1;i<=5;i++)
        x[i]=a%10,a/=10;
    for(int i=6;i<=10;i++)
        x[i]=b%10,b/=10;
    for(int i=1;i<=10;i++)
        for(int j=i+1;j<=10;j++)
            if(x[i]==x[j])
                return false;
    return true;
}

inline void print(int x)
{
    if(x<10000)
        printf("0");
    printf("%d",x);
    return;
}

int main()
{
    int n,t=0;
    while(scanf("%d",&n) && n)
    {
        if(t++)
            printf("\n");
        bool flag=0;
        for(int i=1234;i<=98765;i++)
        {
            if(!chk(i,i*n))
                continue;
            else 
            {
                print(i*n);
                printf(" / ");
                print(i);
                printf(" = %d\n",n);
                flag=1;
            }
        }
        if(!flag)
            printf("There are no solutions for %d.\n",n);
    }
    return 0;
}