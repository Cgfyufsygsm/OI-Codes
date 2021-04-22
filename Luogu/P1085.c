#include <stdio.h>
int main()
{
    int a,b,c,i,max=0,day=0;
    for(i=1;i<=7;i++)
    {
        scanf("%d%d",&a,&b);
        c=a+b;
        if(c>max && c>8)
        {
            max=c;
            day=i;
        }
        
    }
    printf("%d",day);
    return 0;
}