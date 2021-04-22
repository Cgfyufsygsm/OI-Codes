#include <stdio.h>
int main()
{
    double a;
    scanf("%lf",&a);
    if(a<=150)
        printf("%.1lf",0.4463*a);
    else
    {
        if(a<=400)
            printf("%.1lf",66.945+0.4663*(a-150));
        else
            printf("%.1lf",183.52+0.5663*(a-400));
    }
    return 0;
}