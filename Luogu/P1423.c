#include<stdio.h>
int main()
{
    int count,i;
    float goal,can=2,have=0;//goal表示目标，can表示这一次能跑的，have表示已经走的
    scanf("%f",&goal);
    for(i=1;;i++)
    {
        if(i>1)
            can*=0.98;
        have+=can;
        count++;
        if(have>=goal)
            break;
    }
    printf("%d",count);
    return 0;
}