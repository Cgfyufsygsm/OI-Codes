#include<stdio.h>
int main()
{
    int cost,money=0,flag=1,month,mom=0,i;
    for(i=1;i<=12;i++)
    {
        money+=300;
        scanf("%d",&cost);
        money-=cost;
        if(money<0)
        {
            flag=0;
            month=i;
            break;
        }
        mom=mom+(money/100);
        money%=100;
        
    }
    if(flag==0)
    {
        printf("%d",(-1)*month);
    }
    else
    {
        mom*=120;
        money+=mom;
        printf("%d",money);
    }
    return 0;
}