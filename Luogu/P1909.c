#include<stdio.h>
#include<limits.h>
int main()
{
    int n,i,a,b,money,min=INT_MAX;//n为需要数量，a每包数量，b价格
    scanf("%d",&n);
    for(i=1;i<=3;i++)
    {
        scanf("%d%d",&a,&b);
        money=(n/a)*b;
        if(n%a!=0)
            money+=b;
        if(money<min)
            min=money;
    }
    printf("%d",min);
    return 0;
}