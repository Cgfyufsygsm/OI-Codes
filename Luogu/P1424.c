#include<stdio.h>
int main()
{
    int x;
    long int n,zhounei,zhouwai,zhengseven,yu;
    scanf("%d%ld",&x,&n);
    if(x<=6)
        zhounei=(6-x)*250;
    else
        zhounei=0;
    zhouwai=n-(8-x);
    zhengseven=(zhouwai/7)*1250;
    if(zhouwai%7<=5)
    {
        yu=(zhouwai%7)*250;
    }
    else
    {
        yu=1250;
    }
    printf("%ld",zhounei+zhengseven+yu);
    return 0;
}