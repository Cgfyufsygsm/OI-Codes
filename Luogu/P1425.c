#include <stdio.h>
int main()
{
    int a,b,c,d,min;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    min=60*(c-a)+(d-b);
    printf("%d %d",(min/60),(min%60));
    return 0;
}